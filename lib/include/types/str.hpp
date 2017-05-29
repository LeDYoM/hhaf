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
		constexpr str() : std::string{} {}
		constexpr str(const std::string &source) : std::string{ source } {}
		//		str(str&&rhs) = default;
		//		str &operator=(const std::string &source) { static_cast<std::string>(*this) = source; return *this; }
		//		str &operator=(const str &source) = default;

		std::vector<str> split(const char separator) const;
		str &append(const unsigned int n);
		str &append(const signed int n);
		str &append(const str &n);

	};

	static_assert(std::is_move_constructible_v<str>, "str must be movable");
	static_assert(std::is_move_assignable_v<str>, "str must be movable");
	using string_vector = std::vector<str>;
}

#endif
