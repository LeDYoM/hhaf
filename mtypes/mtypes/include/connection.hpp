#pragma once

#ifndef LIB_CONNECTION_INCLUDE_HPP
#define LIB_CONNECTION_INCLUDE_HPP

#include "function.hpp"
#include "vector.hpp"

namespace lib
{
	template <typename> 
	class emmiter;

	template <typename... Args>
	class emmiter<Args...> final {
	public:
		constexpr emmiter() = default;
		constexpr emmiter (const emmiter &) = default;
		constexpr emmiter & operator=(const emmiter &) = default;
		constexpr emmiter(emmiter &&) = default;
		constexpr emmiter & operator=(emmiter &&) = default;

		constexpr void operator()(Args... args) {
			if (!m_receivers.empty()) {
				for (auto &f : m_receivers) {
					f(std::forward<Args>(args)...);
				}
			}
		}

		constexpr bool connect(function<void(Args...)> f) {
			m_receivers.emplace_back(ir,std::move(f));
			return true;
		}

	private:
		vector<function<void(Args...)>> m_receivers;
	};

	template <typename... Args>
	class connection<Args...> final {
	public:
		constexpr connection(emmiter<Args...> &e, function<void(Args...)> f) : m_emmiter{ e }, m_function{ f } {
			m_emitter.connect(m_function);
		}
	private:
		emitter<Args...> &m_emmiter;
		function<void(Args...)> &m_function;
	};

#endif
