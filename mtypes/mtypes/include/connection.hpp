#pragma once

#ifndef LIB_CONNECTION_INCLUDE_HPP
#define LIB_CONNECTION_INCLUDE_HPP

#include "function.hpp"
#include "vector.hpp"

namespace lib
{
	template <typename... Args>
	class emitter final {
	public:
		constexpr emitter() = default;
		constexpr emitter(function<void(Args...)> f) : m_receivers{ std::move(f) } {}
		constexpr emitter(const emitter &) = default;
		constexpr emitter & operator=(const emitter &) = default;
		constexpr emitter(emitter &&) = default;
		constexpr emitter & operator=(emitter &&) = default;

		constexpr void operator()(Args&&... args) {
			if (!m_receivers.empty()) {
				for (auto &f : m_receivers) {
					f(std::forward<Args>(args)...);
				}
			}
		}

		constexpr void connect(function<void(Args...)> f) {
			m_receivers.emplace_back(std::move(f));
		}

		template <typename T, typename V>
		constexpr void connect(T&& t, V&& b) {
			m_receivers.emplace_back(std::forward<T>(t),std::forward<V>(b));
		}

		constexpr bool disconnect(function<void(Args...)>& f) {
			auto where_it_was = m_receivers.remove_value(f);
			return where_it_was != m_receivers.end();
		}

	private:
		vector<function<void(Args...)>> m_receivers;
	};

	class iconnection
	{
	public:
		virtual bool disconnect() = 0;
		virtual ~iconnection() {}
	};

	template <typename... Args>
	class connection final : public iconnection {
	public:
		constexpr connection(emitter<Args...> &e, function<void(Args...)> f) : m_emitter{ e }, m_function{ std::move(f) } {
			m_emitter.connect(m_function);
		}

		inline bool disconnect() override {
			return m_emitter.disconnect(m_function);
		}
	private:
		emitter<Args...> &m_emitter;
		function<void(Args...)> m_function;
	};

	class ireceiver
	{
	public:
		template <typename R, typename... Args>
		constexpr void connect(emitter<Args...> &e, R f) {
			m_connections.push_back(msptr<connection<Args...>>(e, std::move(f)));
		}
		
		~ireceiver() 
		{
			for (auto &connection : m_connections) {
				connection->disconnect();
			}
		}
	private:
		vector<sptr<iconnection>> m_connections;
	};
}

#endif
