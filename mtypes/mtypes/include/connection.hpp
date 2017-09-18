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
				for (auto &f : m_receivers) {
					f(std::forward<Args>(args)...);
				}
			}
		}

		constexpr void connect(function<void(Args...)> f) {
			m_receivers.emplace_back(std::move(f));
		}

		constexpr bool disconnect(function<void(Args...)>& f) {
			auto where_it_was = m_receivers.remove_value(f);
			return where_it_was != m_receivers.end();
		}

	private:
		vector<function<void(Args...)>> m_receivers;
	};

	template <typename>
	class connection;

	template <typename... Args>
	class connection<Args...> final {
	public:
		constexpr connection(emitter<Args...> &e, function<void(Args...)> f) : m_emitter{ e }, m_function{ f } {
			m_emitter.connect(m_function);
		}

		bool disconnect() {
			return m_emitter.disconnect(m_function);
		}
	private:
		emitter<Args...> &m_emitter;
		function<void(Args...)> &m_function;
	};
}

#endif
