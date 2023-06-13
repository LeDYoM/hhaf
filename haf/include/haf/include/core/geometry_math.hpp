HAF_PRAGMA_ONCE
#ifndef HAF_MATH_GEOMETRY_MATH_INCLUDE_HPP
#define HAF_MATH_GEOMETRY_MATH_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/vector3d.hpp>
#include <facil_math/include/vector4d.hpp>
#include <facil_math/include/rect.hpp>

namespace haf::math
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

[[nodiscard]] core::f32 length(fmath::vector4df const& v);
[[nodiscard]] core::f32 length(fmath::vector3df const& v);
[[nodiscard]] core::f32 length(fmath::vector2df const& v);
[[nodiscard]] fmath::vector4df normalize(fmath::vector4df const& v);
[[nodiscard]] fmath::vector3df normalize(fmath::vector3df const& v);
[[nodiscard]] fmath::vector2df normalize(fmath::vector2df const& v);
[[nodiscard]] fmath::vector4df cross(fmath::vector4df const& a,
                                    fmath::vector4df const& b);
[[nodiscard]] fmath::vector3df cross(fmath::vector3df const& a,
                                    fmath::vector3df const& b);
[[nodiscard]] fmath::vector2df cross(fmath::vector2df const& a,
                                    fmath::vector2df const& b);
[[nodiscard]] core::f32 dot(fmath::vector4df const& a, fmath::vector4df const& b);
[[nodiscard]] core::f32 dot(fmath::vector3df const& a, fmath::vector3df const& b);
[[nodiscard]] core::f32 dot(fmath::vector2df const& a, fmath::vector2df const& b);

}  // namespace haf::math

#endif
