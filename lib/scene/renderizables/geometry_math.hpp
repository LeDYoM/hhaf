#pragma once

#ifndef LIB_SCENE_GEOMETRY_MATH_INCLUDE_HPP__
#define LIB_SCENE_GEOMETRY_MATH_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <cmath>

namespace lib::scene::nodes
{
    template <typename T>
    static constexpr T PiConstant = 3.14159265358979323846;
    template <typename T>
    static constexpr T PiD2Constant = PiConstant<T> / static_cast<T>(2);
}

#endif
