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

    constexpr basic_str_literal(char_type const (&str)[N]) noexcept :
        real_size_{N}
    {
        std::copy_n(str, N, value);
    }

    template <size_type M>
    constexpr basic_str_literal(char_type const (&str)[M]) noexcept :
        real_size_{M}
    {
        static_assert(M < N, "Invalid initialization parameter");
        std::copy_n(str, M, value);
        std::fill(&(value[M]), &(value[N]), char_type{0});
    }

    constexpr size_type size() const noexcept { return real_size_ - 1U; }

    constexpr bool empty() const noexcept { return real_size_ == 1U; }

    constexpr char_type const* const cbegin() const noexcept { return value; }
    constexpr char_type const* const cend() const noexcept
    {
        return &(value[real_size_]);
    }

    constexpr bool operator==(basic_str_literal const& rhs) const noexcept
    {
        if (size() == rhs.size())
        {
            return std::equal(cbegin(), cend(), rhs.cbegin(), rhs.cend());
        }
        else
        {
            return false;
        }
    }

    constexpr bool operator!=(basic_str_literal const& rhs) const noexcept
    {
        return !(*this == rhs);
    }

    template <size_type N2>
    constexpr bool operator==(
        basic_str_literal<char_type, N2> const&) const noexcept
    {
        return false;
    }

    template <size_type N2>
    constexpr bool operator!=(
        basic_str_literal<char_type, N2> const&) const noexcept
    {
        return true;
    }

    template <size_type N2>
    constexpr bool operator==(char_type const (&rhs)[N2]) const
    {
        if (size() == (N2 - 1U))
        {
            return std::equal(cbegin(), cend(), rhs, (rhs + N2));
        }
        else
        {
            return false;
        }
    }

    constexpr bool operator==(basic_str_literal&& rhs) const
    {
        if (size() == rhs.size())
        {
            return std::equal(cbegin(), cend(), rhs.cbegin(), rhs.cend());
        }
        else
        {
            return false;
        }
    }

    constexpr bool operator!=(basic_str_literal&& rhs) const noexcept
    {
        return !(*this == std::move(rhs));
    }

    template <size_type N2>
    constexpr bool operator==(
        basic_str_literal<char_type, N2>&& rhs) const noexcept
    {
        if (size() == (N2 - 1U))
        {
            return std::equal(cbegin(), cend(), rhs, (rhs + N));
        }
        else
        {
            return false;
        }
    }

    template <size_type N2>
    constexpr bool operator!=(
        basic_str_literal<char_type, N2>&& rhs) const noexcept
    {
        return !(*this == std::move(rhs));
    }

    constexpr size_type hash() const noexcept { return value[0]; }

    const size_type real_size_;
    char_type value[N];
};

template <size_type N>
using str_literal = basic_str_literal<char, N>;

using str_literal_hash = size_type;

template <size_type N>
constexpr size_type basic_str_literal_size(char const (&str)[N]) noexcept
{
    return N - 1U;
}

}  // namespace htps

#endif
