#pragma once

#ifndef MTYPES_OPTIONAL_INCLUDE_HPP
#define MTYPES_OPTIONAL_INCLUDE_HPP

#include <optional>

namespace lib
{
	template <typename T>
	class  optional {
	public:
		using value = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;

		constexpr optional() = default;
		constexpr optional(const T &value) {
			*this = optional(value);
		}

		constexpr optional& operator=(const T &value) {
			m_value = muptr<T>(value);
		}

		constexpr bool empty() const noexcept { return m_value != nullptr; }
		constexpr T &operator() { return *m_value; }
		constexpr const T &operator() const { return *m_value; }

	private:
		uptr<T> m_value;
	};
}

#endif
