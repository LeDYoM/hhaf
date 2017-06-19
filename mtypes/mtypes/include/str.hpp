#pragma once

#ifndef LIB_STR_INCLUDE_HPP
#define LIB_STR_INCLUDE_HPP

#include <string>
#include "mtypes_export.h"
#include "vector.hpp"

namespace lib
{
	struct MTYPES_EXPORT inline_str
	{
		inline_str(const char *_str, unsigned int _size) : str{_str}, size{_size} {}

		const char *str;
		unsigned int size;

	};

// Temporary code
#pragma warning(push)
#pragma warning(disable:4251)
	class MTYPES_EXPORT str : public ::std::string
	{
#pragma warning(pop)
	public:
		str() = default;
		str(const inline_str &source) : std::string{ source.str } {}
		str(const std::string &source) : std::string{ source } {}
		str(std::string &&source) : std::string{ std::move(source) } {}

		str(const char c);
		str(const unsigned int n);
		str(const signed int n);
		str(const str &n);
		str(const char *n);
		str(const float n);
		str(const double n);

		vector<str> split(const char separator) const;
		str &append() { return *this; }
		str &append(const char c);
		str &append(const unsigned int n);
		str &append(const signed int n);
		str &append(const str &n);
		str &append(const char *n);
		str &append(const float n);
		str &append(const double n);

		reference operator[](const size_type index) { return std::string::operator[](index); }
		const_reference operator[](const size_type index) const { return std::string::operator[](index); }
		iterator begin() { return std::string::begin(); }
		const_iterator begin() const { return std::string::begin(); }
		const_iterator cbegin() const { return std::string::cbegin(); }
		iterator end() { return std::string::end(); }
		const_iterator end() const { return std::string::end(); }
		const_iterator cend() const { return std::string::cend(); }

		inline_str ic_str() const noexcept { return {c_str(), size()}; }
		const char *c_str() const noexcept { return std::string::c_str(); }
		bool empty() const noexcept { return std::string::empty(); }
		template <typename T>
		str &operator<<(const T&n)
		{
			return append(n);
		}

		template <typename T>
		str operator+(const T&n) const
		{
			return str(*this).append(n);
		}

	};

//	bool operator==(const str& lhs, const str&rhs) noexcept { 
//		return operator==(std::string(lhs.c_str()), std::string(rhs.c_str())); 
//	}

//	bool operator!=(const str& lhs, const str&rhs) noexcept {
//		return !operator==(std::string(lhs.c_str()), std::string(rhs.c_str()));
//	}

	static_assert(std::is_move_constructible_v<str>, "str must be movable");
	static_assert(std::is_move_assignable_v<str>, "str must be movable");
	using string_vector = vector<str>;
}

#endif
