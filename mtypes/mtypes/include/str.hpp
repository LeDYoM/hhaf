#pragma once

#ifndef LIB_STR_INCLUDE_HPP
#define LIB_STR_INCLUDE_HPP

#include "mtypes_export.hpp"
#include "vector.hpp"
#include "types.hpp"

namespace lib
{
	using char_type = char;

	using char_type = char;

	class MTYPES_EXPORT str
	{
		using reference = char_type&;
		using const_reference = const char_type&;
		using iterator = char_type*;
		using const_iterator = const char_type*;
		using size_type = unsigned int;
		// Temporary code
		#pragma warning(push)
		#pragma warning(disable:4251)
		vector<char_type> m_data;
		#pragma warning(pop)
	public:
		constexpr str() noexcept = default;

		template<size_t N>
		constexpr str(const char_type(&a)[N]) noexcept : str(inline_str{ a,N }) {}

		str(str&&) noexcept = default;

		constexpr str(const char_type c) noexcept : m_data{ c,0 } {}
		constexpr str(const str & n) noexcept : m_data{ n.m_data } {}
		str(const u32 n);
		str(const s32 n);
		str(const char_type *n) noexcept;
		str(const f32 n);
		str(const f64 n);

		str&operator=(const str&);
		str&operator=(str&&) noexcept;
		vector<str> split(const char_type separator) const;
		str &append() { return *this; }
		str &append(const char_type c);
		str &append(const u32 n);
		str &append(const s32 n);
		str &append(const str &n);
		str &append(const char_type *n);
		str &append(const f32 n);
		str &append(const f64 n);
		void convert(u32 &n) const;
		void convert(s32 &n) const;
		void convert(f32 &n) const;
		void convert(f64 &n) const;

		template <typename T>
		str &operator+=(T&&source) {
			return append(std::forward<T>(source));
		}

		constexpr size_t size() const noexcept{ return m_data.empty()?0:m_data.size()-1; }
		constexpr reference operator[](const size_type index) noexcept { return m_data[index]; }
		constexpr const_reference operator[](const size_type index) const noexcept { return m_data[index]; }
		constexpr iterator begin() noexcept { return m_data.begin(); }
		constexpr const_iterator begin() const noexcept { return m_data.begin(); }
		constexpr const_iterator cbegin() const noexcept { return m_data.cbegin(); }
		constexpr iterator end() noexcept { return m_data.begin()+size(); }
		constexpr const_iterator end() const noexcept { return m_data.begin()+size(); }
		constexpr const_iterator cend() const noexcept { return m_data.cbegin()+size(); }

		constexpr const char *c_str() const noexcept { return m_data.cbegin(); }
		constexpr bool empty() const noexcept { return m_data.empty(); }
		template <typename T>
		constexpr str &operator<<(const T&n)
		{
			return append(n);
		}

		template <typename enum_type>
		std::enable_if_t<std::is_enum<enum_type>::value>
		constexpr operator>>(enum_type&n) const
		{
			std::underlying_type_t<enum_type> tmp{};
			convert(tmp);
			n = static_cast<typename enum_type>(tmp);
		}

		template <typename T>
		std::enable_if_t<!std::is_enum<T>::value>
		constexpr operator>>(T&n) const
		{
			convert(n);
		}

		template <>
		void operator>>(str&n) const
		{
			n = *this;
		}

		friend constexpr bool operator==(const str& lhs, const str&rhs) noexcept;
		friend constexpr bool operator!=(const str& lhs, const str&rhs) noexcept;
		friend constexpr bool operator<(const str& lhs, const str&rhs) noexcept;
		friend str operator+(const str& lhs, const str&rhs) noexcept;
	};


	constexpr bool operator==(const str& lhs, const str&rhs) noexcept { 
		return lhs.m_data == rhs.m_data;
	}

	constexpr bool operator!=(const str& lhs, const str&rhs) noexcept {
		return lhs.m_data != rhs.m_data;
	}

	constexpr bool operator<(const str& lhs, const str&rhs) noexcept {
		size_t i{ 0 };
		while (i < lhs.size() && i < rhs.size()) {
			if (lhs[i] < rhs[i]) {
				return true;
			}
			else if (lhs[i] > rhs[i]) {
				return false;
			}
			++i;
		}
		return lhs.size() < rhs.size();
	}

	inline str operator+(const str& lhs, const str&rhs) noexcept {
		return str(lhs).append(rhs);
	}

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
		return str(std::forward<T>(arg));
	}

	template<typename T, typename ...Args>
	constexpr void make_str_internal(str &buffer, T&& arg, Args&&... args)
	{
		make_str_internal(buffer, std::forward<T>(arg));
		make_str_internal(buffer, std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr void make_str_internal(str &buffer, T&& arg)
	{
		buffer << std::forward<T>(arg);
	}

	static_assert(std::is_move_constructible_v<str>, "str must be movable");
	static_assert(std::is_move_assignable_v<str>, "str must be movable assignable");
	using string_vector = vector<str>;
}

#endif
