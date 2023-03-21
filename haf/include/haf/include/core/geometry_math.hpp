HTPS_PRAGMA_ONCE
#ifndef HAF_MATH_GEOMETRY_MATH_INCLUDE_HPP
#define HAF_MATH_GEOMETRY_MATH_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <htypes/include/vector2d.hpp>
#include <htypes/include/vector3d.hpp>
#include <htypes/include/vector4d.hpp>
#include <htypes/include/rect.hpp>

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

[[nodiscard]] core::f32 length(core::vector4df const& v);
[[nodiscard]] core::f32 length(core::vector3df const& v);
[[nodiscard]] core::f32 length(core::vector2df const& v);
[[nodiscard]] core::vector4df normalize(core::vector4df const& v);
[[nodiscard]] core::vector3df normalize(core::vector3df const& v);
[[nodiscard]] core::vector2df normalize(core::vector2df const& v);
[[nodiscard]] core::vector4df cross(core::vector4df const& a,
                                    core::vector4df const& b);
[[nodiscard]] core::vector3df cross(core::vector3df const& a,
                                    core::vector3df const& b);
[[nodiscard]] core::vector2df cross(core::vector2df const& a,
                                    core::vector2df const& b);
[[nodiscard]] core::f32 dot(core::vector4df const& a, core::vector4df const& b);
[[nodiscard]] core::f32 dot(core::vector3df const& a, core::vector3df const& b);
[[nodiscard]] core::f32 dot(core::vector2df const& a, core::vector2df const& b);

}  // namespace haf::math

#endif
