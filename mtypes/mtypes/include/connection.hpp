#pragma once

#ifndef LIB_CONNECTION_INCLUDE_HPP
#define LIB_CONNECTION_INCLUDE_HPP

#include "function.hpp"
#include "vector.hpp"

namespace lib
{
	template <typename> 
	class connection;

	template <typename... Args>
	class connection<Args...> final {
	public:
		constexpr connection() = default;
		constexpr connection (const connection &) = default;
		constexpr connection & operator=(const connection &) = default;
		constexpr connection(connection &&) = default;
		constexpr connection & operator=(connection &&) = default;

		constexpr void operator()(Args... args) {
			if (!m_receivers.empty()) {
				for (auto &f : m_receivers) {
					f(std::forward<Args>(args)...);
				}
			}
		}

		constexpr bool connect(function<void(Args...)> f) {
			m_receivers.push_back(std::move(f));
			return true;
		}

	private:
		vector<function<void(Args...)>> m_receivers;
	};
}

#endif
