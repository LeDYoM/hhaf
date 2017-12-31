#pragma once

#ifndef LIB_STR_INCLUDE_HPP
#define LIB_STR_INCLUDE_HPP

#include "mtypes_export.hpp"
#include "vector.hpp"
#include "types.hpp"
#include <type_traits>

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
		// Temporary code
#ifdef _MSC_VER
		#pragma warning(push)
		#pragma warning(disable:4251)
#endif
		vector<char_type> m_data;
#ifdef _MSC_VER
		#pragma warning(pop)
#endif
	public:
		constexpr str() noexcept : m_data() {}

		template<size_t N>
		constexpr str(const char_type(&a)[N]) noexcept : m_data( a,N ) {}

		constexpr str(str&&) noexcept = default;

		constexpr str(const str & n) noexcept : m_data( n.m_data ) {}
		constexpr str(const char_type *n, const size_t N) noexcept : m_data(n, N+1) {}

		str(const u32 n);
		str(const s32 n);
		str(const char_type *n) noexcept;
		str(const f32 n);
		str(const f64 n);
		str(const char_type c) : str{ &c,1 } {}
		str(const unsigned long n);

		inline str&operator=(const str&rhs) noexcept {
			m_data = rhs.m_data;
			return *this;
		}

		constexpr str&operator=(str&&) noexcept = default;

		vector<str> split(const char_type separator) const;

		constexpr void pop_char() noexcept{
			m_data.pop_back();
		}

		constexpr str &append() { return *this; }

		str & append(const u32 n) {
			append(str(n));
			return *this;
		}

		str & append(const s32 n) {
			append(str(n));
			return *this;
		}

		str & append(const str & n) {
			m_data.pop_back();
			m_data.insert(n.m_data);
			return *this        ;
		}

		str & append(const char_type * n) {
			append(str(n));
			return *this;
		}

		str & append(const f32 n) {
			append(str(n));
			return *this;
		}

		str & append(const f64 n) {
			append(str(n));
			return *this;
		}

		str & append(const long unsigned n) {
			append(str(n));
			return *this;
		}

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
		constexpr str &operator<<(const T&n) {
			return append(n);
		}

		template <typename T>
		constexpr str& operator>>(T &n) {
            if constexpr (std::is_enum_v<T>) {
       			std::underlying_type_t<T> tmp{};
                convert(tmp);
                n = static_cast<T>(tmp);
            } else if constexpr (std::is_same_v<T,str>) {
                n = *this;
            } else {
                convert(n);
            }
            return *this;
        }

		friend constexpr bool operator==(const str& lhs, const str&rhs) noexcept;
		friend constexpr bool operator!=(const str& lhs, const str&rhs) noexcept;
		friend bool operator<(const str& lhs, const str&rhs) noexcept;
		friend str operator+(const str& lhs, const str&rhs) noexcept;
	};


	constexpr bool operator==(const str& lhs, const str&rhs) noexcept {
		return lhs.m_data == rhs.m_data;
	}

	constexpr bool operator!=(const str& lhs, const str&rhs) noexcept {
		return lhs.m_data != rhs.m_data;
	}

	inline bool operator<(const str& lhs, const str&rhs) noexcept {
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
