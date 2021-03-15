#ifndef MTPS_CESTR_INCLUDE_HPP
#define MTPS_CESTR_INCLUDE_HPP

#include "types.hpp"

namespace mtps
{

template <size_type N>
struct cestr
{
    constexpr cestr(char const (&str)[N]) { std::copy_n(str, N, value); }

    constexpr size_type size() const noexcept { return N - 1U; }

    constexpr bool empty() const noexcept { return N < 2U; }

    template <size_type N2>
    constexpr bool operator==(char const (&str)[N2]) const
    {
        if (N != N2)
        {
            return false;
        }
        else
        {
            return std::equal(std::cbegin(value), std::cend(value), std::cbegin(str),
                       std::cend(str));
        }
    }

    char value[N];
};

}  // namespace mtps

#endif
