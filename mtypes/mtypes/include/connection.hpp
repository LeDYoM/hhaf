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

		constexpr bool connect(function<void(Args...)> f) {
			m_receivers.emplace_back(std::move(f));
			return true;
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
	private:
		emitter<Args...> &m_emmiter;
		function<void(Args...)> &m_function;
	};
}

#endif
