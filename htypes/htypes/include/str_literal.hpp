#ifndef MTPS_CESTR_INCLUDE_HPP
#define MTPS_CESTR_INCLUDE_HPP

#include "types.hpp"
#include <algorithm>

namespace htps
{

template <typename char_type, size_type N>
struct basic_str_literal
{
    using size_type = size_type;

    constexpr basic_str_literal(char_type const (&str)[N]) noexcept
    {
        std::copy_n(str, N, value);
    }

    constexpr size_type size() const noexcept { return N - 1U; }

    constexpr bool empty() const noexcept { return N == 1U; }

    constexpr char_type const * const cbegin() const noexcept { return value; }
    constexpr char_type const * const cend() const noexcept { return &(value[N]); }

    constexpr bool operator==(char_type const (&rhs)[N]) const
    {
        return std::equal(cbegin(), cend(), rhs, (rhs + N));
    }

    template <size_type N2>
    constexpr bool operator==(char_type const (&)[N2]) const
    {
        return false;
    }

    constexpr bool operator==(basic_str_literal const& rhs) const
    {
        return std::equal(cbegin(), cend(), rhs.cbegin(), rhs.cend());
    }

    template <size_type N2>
    constexpr bool operator==(basic_str_literal<char_type, N2> const&) const
    {
        return false;
    }

    constexpr bool operator==(basic_str_literal&& rhs) const
    {
        return std::equal(cbegin(), cend(), rhs.cbegin(), rhs.cend());
    }

    template <size_type N2>
    constexpr bool operator==(basic_str_literal<char_type, N2>&&) const
    {
        return false;
    }

    constexpr size_type hash() const noexcept
    {
        return value[0];
    }

    char_type value[N];

};

template <size_type N>
using str_literal = basic_str_literal<char, N>;

using str_literal_hash = size_type;
}  // namespace htps

#endif
