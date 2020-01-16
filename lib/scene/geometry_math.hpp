#pragma once

#ifndef LIB_SCENE_GEOMETRY_MATH_INCLUDE_HPP
#define LIB_SCENE_GEOMETRY_MATH_INCLUDE_HPP

namespace lib::scene
{
    template <typename T>
    static constexpr T PiConstant = static_cast<T>(3.14159265358979323846);
    template <typename T>
    static constexpr T PiD2Constant = PiConstant<T> / static_cast<T>(2);
    template <typename T>
    static constexpr T PiM2Constant = PiConstant<T> * static_cast<T>(2);
    template <typename T>
    static constexpr T PiMDConstant = PiConstant<T> * static_cast<T>(1.5);

}

#endif
