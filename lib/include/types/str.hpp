#pragma once

#ifndef LIB_STR_INCLUDE_HPP
#define LIB_STR_INCLUDE_HPP

#include <string>
#include <vector>
#include "../lib.hpp"

namespace lib
{
	class LIB_API str : public std::string
	{
	public:
		using std::string::string;

		str() = default;
		str(const std::string &source) : std::string{ source } {}
		str(const unsigned int n);
		str(const signed int n);
		str(const str &n);
		str(const char *n);
		str(const float n);
		str(const double n);

		std::vector<str> split(const char separator) const;
		str &append() { return *this; }
		str &append(const unsigned int n);
		str &append(const signed int n);
		str &append(const str &n);
		str &append(const char *n);
		str &append(const float n);
		str &append(const double n);

		template <typename T>
		str &operator<<(const T&n)
		{
			return append(n);
		}

		template <typename... T>
		str &operator<<(T... n)
		{
			return append(n...);
		}

	};

	static_assert(std::is_move_constructible_v<str>, "str must be movable");
	static_assert(std::is_move_assignable_v<str>, "str must be movable");
	using string_vector = std::vector<str>;
}

#endif
