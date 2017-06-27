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
		const char *begin() const { return str; }
		const char *end() const { return str + size; }
		const char *str;
		unsigned int size;

	};

	using char_type = char;

	class MTYPES_EXPORT str
	{
		using reference = char_type&;
		using const_reference = const char_type&;
		using iterator = char_type*;
		using const_iterator = const char_type*;
		using size_type = unsigned int;
		vector<char_type> m_data;
	public:
		str();
		str(inline_str);
		template<size_t N>
		constexpr str(const char_type(&a)[N]) : str(inline_str{ a,N }) {}
		str(const std::string &);
//		str(std::string &&);
		str(str&&);

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

		size_t size() const noexcept{ return m_data.size(); }
		reference operator[](const size_type index) { return m_data[index]; }
		const_reference operator[](const size_type index) const { return m_data[index]; }
		iterator begin() { return m_data.begin(); }
		const_iterator begin() const { return m_data.begin(); }
		const_iterator cbegin() const { return m_data.cbegin(); }
		iterator end() { return m_data.end(); }
		const_iterator end() const { return m_data.end(); }
		const_iterator cend() const { return m_data.cend(); }

		inline_str ic_str() const noexcept { return {c_str(), size()}; }
		const char *c_str() const noexcept { return m_data.cbegin(); }
		bool empty() const noexcept { return m_data.empty(); }
		template <typename T>
		constexpr str &operator<<(const T&n)
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

	template<typename ...Args>
	constexpr str make_str(Args&&... args)
	{
		str t;
		make_str_internal(t, std::forward<Args>(args)...);
		return t;
	}

	template<typename T>
	constexpr str make_str(T&& arg)
	{
		return str(arg);
	}

	template<typename T, typename ...Args>
	constexpr void make_str_internal(str &buffer, T&& arg, Args&&... args)
	{
		make_str_internal(buffer, arg);
		make_str_internal(buffer, std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr void make_str_internal(str &buffer, T&& arg)
	{
		buffer<< arg;
	}

	static_assert(std::is_move_constructible_v<str>, "str must be movable");
	static_assert(std::is_move_assignable_v<str>, "str must be movable assignable");
	using string_vector = vector<str>;
}

#endif
