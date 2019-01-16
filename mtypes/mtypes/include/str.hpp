#pragma once

#ifndef LIB_STR_INCLUDE_HPP
#define LIB_STR_INCLUDE_HPP

#include "vector.hpp"
#include "types.hpp"
#include "mtypes_export.hpp"

#include <type_traits>
#include <algorithm>
#include <cctype>

namespace lib
{
    using char_type = char;

    class MTYPES_EXPORT str
    {
        using reference = char_type&;
        using const_reference = const char_type&;
        using iterator = char_type*;
        using const_iterator = const char_type*;
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

        template<size_type N>
		constexpr str(const char_type(&a)[N]) noexcept : m_data( a,N ) {}

        constexpr str(str&&) noexcept = default;

		constexpr str(const str & n) noexcept : m_data( n.m_data ) {}
		explicit str(const char_type *n) noexcept;
		constexpr str(const char_type *n, const size_type N) noexcept : m_data(n, N+1) {}
        
        constexpr str(const_iterator _begin, const_iterator _end) : m_data{_begin, _end } 
        {
            if (m_data[size() - 1] != 0U)
            {
                m_data.push_back(0U);
            }
        }

        str(const u64 n);
		str(const s64 n);
		str(const u32 n);
		str(const s32 n);	
		str(const f32 n);
		str(const f64 n);

        str&operator=(str&&) noexcept = default;

        constexpr str&operator=(const str&rhs) noexcept 
        {
            m_data = rhs.m_data;
            return *this;
        }

        vector<str> split(const char_type separator) const;

        constexpr void pop_char() noexcept 
        {
            m_data.pop_back();
        }

        inline bool starts_with(const str& prefix) const noexcept
        {
            if (size() < prefix.size())
            {
                return false;
            }

            return (substr(0, prefix.size()) == prefix);
        }

        inline bool ends_with(const str& prefix) const noexcept
        {
            if (size() < prefix.size())
            {
                return false;
            }

            return (substr(size() - prefix.size()) == prefix);
        }

        str substr(size_type start, size_type len = npos) const;

        constexpr str &append() { return *this; }

        str & append(const str & n) {
            m_data.pop_back();
            m_data.insert(n.m_data);
            return *this;
        }

		template<size_type N>
		constexpr str &append(const char_type(&n)[N]) {
			append(str(std::forward<const char_type(&)[N]>(n)));
			return *this;
		}

        str & append(const char_type * n) {
            append(str(n));
            return *this;
        }

		str & append(const u64 n) {
			append(str(n));
			return *this;
		}

		str & append(const s64 n) {
			append(str(n));
			return *this;
		}

		str & append(const u32 n) {
			append(str(n));
			return *this;
		}

		str & append(const s32 n) {
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

		bool convert(u64 &n) const;
		bool convert(s64 &n) const;
		bool convert(u32 &n) const;
		bool convert(s32 &n) const;
		bool convert(u16 &n) const;
		bool convert(s16 &n) const;
		bool convert(f32 &n) const;
		bool convert(f64 &n) const;

        template <typename T>
        str &operator+=(T&&source) {
            return append(std::forward<T>(source));
        }

        str &operator+=(const str&source) {
            return append(source);
        }

        constexpr size_type size() const noexcept{ return m_data.empty()?0:m_data.size()-1; }

        inline void ltrim() 
        {
            if (!empty())
            {
                for (size_type index = 0U; index < size(); ++index)
                {
                    if (!std::isspace(static_cast<unsigned char>(m_data[index])))
                    {
                        *this = substr(index);
                        return;
                    }
                }
                *this = "";
            }
        }

        // trim from end (in place)
        inline void rtrim()
        {
            if (!empty())
            {
                for (size_type index = size() - 1; index > 0; --index)
                {
                    if (!std::isspace(static_cast<unsigned char>(m_data[index])))
                    {
                        *this = substr(0U, index + 1U);
                        return;
                    }
                }
         
                *this = (std::isspace(static_cast<unsigned char>(m_data[0U])))
                ? "" : substr(0U, 1U);
            }
        }

        // trim from both ends (in place)
        inline void trim()
        {
            ltrim();
            rtrim();
        }

        //TO DO: Change them by using, eg.
        // using vector<T>::begin();
        constexpr reference operator[](const size_type index) noexcept { return m_data[index]; }
        constexpr const_reference operator[](const size_type index) const noexcept { return m_data[index]; }
        constexpr iterator begin() noexcept { return m_data.begin(); }
        constexpr const_iterator begin() const noexcept { return m_data.begin(); }
        constexpr const_iterator cbegin() const noexcept { return m_data.cbegin(); }
        constexpr iterator end() noexcept { return m_data.begin()+size(); }
        constexpr const_iterator end() const noexcept { return m_data.begin()+size(); }
        constexpr const_iterator cend() const noexcept { return m_data.cbegin()+size(); }

        constexpr const char_type *const c_str() const noexcept { return m_data.cbegin(); }
        constexpr bool empty() const noexcept { return size() == 0; }

        constexpr size_type find_first_of(const char_type chValue) const noexcept 
        {
            const auto iterator(m_data.cfind(chValue));

            if (iterator != m_data.cend()) 
            {
                return iterator - m_data.cbegin();
            }
            return npos;
        }

        template <typename T>
        constexpr str &operator<<(const T&n) {
            return append(n);
        }

        template <typename T>
        constexpr str& operator>>(T &n)
        {
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

        static const size_type	npos = static_cast<size_type>(-1);

        friend constexpr bool operator==(const str& lhs, const str&rhs) noexcept;
        friend constexpr bool operator!=(const str& lhs, const str&rhs) noexcept;

        template<size_type N>
        friend constexpr bool operator==(const str& lhs, const char_type(&a)[N]) noexcept;
        template<size_type N>
        friend constexpr bool operator!=(const str& lhs, const char_type(&a)[N]) noexcept;

        friend bool operator<(const str& lhs, const str&rhs) noexcept;
        friend str operator+(const str& lhs, const str&rhs) noexcept;
    };


    constexpr bool operator==(const str& lhs, const str&rhs) noexcept {
        return lhs.m_data == rhs.m_data;
    }

    constexpr bool operator!=(const str& lhs, const str&rhs) noexcept {
        return lhs.m_data != rhs.m_data;
    }

    template<size_type N>
    constexpr bool operator==(const str& lhs, const char_type(&a)[N]) noexcept
    {
        if (lhs.size() != (N-1))
            return false;

        size_type counter{0};
        for (const char_type c : lhs.m_data) {
            if (c != a[counter]) return false;
            ++counter;
        }
        return true;
    }


    template<size_type N>
    constexpr bool operator!=(const str& lhs, const char_type(&a)[N]) noexcept
    {
        return !(operator==(lhs,a));
    }

    inline bool operator<(const str& lhs, const str&rhs) noexcept {
        size_type i{ 0 };
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

    inline str operator+(const str& lhs, const str&rhs) noexcept 
    {
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
        str t;
        make_str_internal(t, std::forward<T>(arg));
        return t;
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
