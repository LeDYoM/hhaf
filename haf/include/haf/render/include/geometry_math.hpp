#pragma once

#ifndef HAF_SCENE_GEOMETRY_MATH_INCLUDE_HPP
#define HAF_SCENE_GEOMETRY_MATH_INCLUDE_HPP

#include <cmath>

namespace haf::scene
{
template <typename T>
static constexpr T PiConstant = static_cast<T>(3.14159265358979323846);
template <typename T>
static constexpr T PiD2Constant = PiConstant<T> / static_cast<T>(2);
template <typename T>
static constexpr T PiM2Constant = PiConstant<T>* static_cast<T>(2);
template <typename T>
static constexpr T PiMDConstant = PiConstant<T>* static_cast<T>(1.5);
template <typename T>
static constexpr T ToRadians = PiConstant<T> / static_cast<T>(180);

template <typename T>
constexpr int sgn(const T val) noexcept
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
constexpr int sgn_cos(T angle)
{
    return sgn(std::cos(angle));
}

template <typename T>
constexpr int sgn_sin(T angle)
{
    return sgn(std::sin(angle));
}

}  // namespace haf::scene

#endif
