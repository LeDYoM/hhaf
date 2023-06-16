HAF_PRAGMA_ONCE
#ifndef HAF_MATH_GEOMETRY_MATH_INCLUDE_HPP
#define HAF_MATH_GEOMETRY_MATH_INCLUDE_HPP

#include <facil_math/include/math_types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/vector3d.hpp>
#include <facil_math/include/vector4d.hpp>
#include <facil_math/include/rect.hpp>

namespace fmath
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

[[nodiscard]] tps::f32 length(vector4df const& v);
[[nodiscard]] tps::f32 length(vector3df const& v);
[[nodiscard]] tps::f32 length(vector2df const& v);
[[nodiscard]] vector4df normalize(vector4df const& v);
[[nodiscard]] vector3df normalize(vector3df const& v);
[[nodiscard]] vector2df normalize(vector2df const& v);
[[nodiscard]] vector4df cross(vector4df const& a, vector4df const& b);
[[nodiscard]] vector3df cross(vector3df const& a, vector3df const& b);
[[nodiscard]] vector2df cross(vector2df const& a, vector2df const& b);
[[nodiscard]] tps::f32 dot(vector4df const& a, vector4df const& b);
[[nodiscard]] tps::f32 dot(vector3df const& a, vector3df const& b);
[[nodiscard]] tps::f32 dot(vector2df const& a, vector2df const& b);

}  // namespace fmath

#endif
