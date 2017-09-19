#pragma once

#ifndef LIB_CONNECTION_INCLUDE_HPP
#define LIB_CONNECTION_INCLUDE_HPP

#include "function.hpp"
#include "vector.hpp"

namespace lib
{
	template <typename>
	class emitter;

	template <typename... Args>
	class emitter<Args...> final {
	public:
		constexpr emitter() = default;
		constexpr emitter(const emitter &) = default;
		constexpr emitter & operator=(const emitter &) = default;
		constexpr emitter(emitter &&) = default;
		constexpr emitter & operator=(emitter &&) = default;

		constexpr void operator()(Args... args) {
			if (!m_receivers.empty()) {
				bool atLeastOneDeleted{ false };
				for (auto &f : m_receivers) {
					if (auto flocked = f.lock()) {
						(*flocked)(std::forward<Args>(args)...);
					}
					else {
						atLeastOneDeleted = true;
					}
				}
				if (atLeastOneDeleted) {
					deleteEmptyEntries();
				}
			}
		}

		constexpr void deleteEmptyEntries() {
			decltype (m_receivers) m_receiversNew;
			for (auto &f : m_receivers) {
				if (auto flocked = f.lock()) {
					m_receiversNew.push_back(f);
				}
			}
			m_receivers.swap(m_receiversNew);
		}

		constexpr void connect(wptr<function<void(Args...)>> f) {
			m_receivers.push_back(std::move(f));
		}

	private:
		vector<wptr<function<void(Args...)>>> m_receivers;
	};

	class IConnection
	{
	public:
		virtual ~IConnection() {}
	};

	template <typename>
	class connection;

	template <typename... Args>
	class connection<Args...> final : public IConnection {
	public:
		constexpr connection(emitter<Args...> &e, sptr<function<void(Args...)>> f) : m_emitter{ e }, m_function{ std::move(f) } {
			m_emitter.connect(m_function);
		}

	private:
		emitter<Args...> &m_emitter;
		sptr<function<void(Args...)>> m_function;
	};

	class Receiver
	{
	public:
		template <typename... Args>
		void connect(emitter<Args...> &e, function<void(Args...)> f) {
			m_connections.push_back(muptr<connection<Args...>>(e, msptr<function<void(Args...)>>(f)));
		}

	private:
		vector<uptr<IConnection>> m_connections;
	};
}

#endif
