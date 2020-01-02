#pragma once

#ifndef MTYPES_MENUM_INCLUDE_HPP
#define MTYPES_MENUM_INCLUDE_HPP

#include <type_traits>
#include <limits>

namespace lib
{

template <typename T>
class MEnum
{
public:
    static constexpr auto min = T::min;
    static constexpr auto max = T::max;
};

} // namespace lib

#endif
