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

    template <size_type N2>
    constexpr bool operator==(char_type const (&rhs)[N2]) const
    {
        if constexpr (N != N2)
        {
            return false;
        }
        else
        {
            return std::equal(std::cbegin(value), std::cend(value),
                              std::cbegin(rhs), std::cend(rhs));
        }
    }

    template <size_type N2>
    constexpr bool operator==(basic_str_literal<char_type, N2> const& rhs) const
    {
        if constexpr (N != N2)
        {
            return false;
        }
        else
        {
            return std::equal(std::cbegin(value), std::cend(value),
                              std::cbegin(rhs), std::cend(rhs));
        }
    }

    template <size_type N2>
    constexpr bool operator==(basic_str_literal<char_type, N2>&& rhs) const
    {
        if constexpr (N != N2)
        {
            return false;
        }
        else
        {
            return std::equal(std::cbegin(value), std::cend(value),
                              std::cbegin(rhs), std::cend(rhs));
        }
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
