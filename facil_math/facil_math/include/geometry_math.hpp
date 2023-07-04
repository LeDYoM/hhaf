FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_GEOMETRY_MATH_INCLUDE_HPP
#define FACIL_MATH_GEOMETRY_MATH_INCLUDE_HPP

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

[[nodiscard]] inline tps::f32 length(vector4df const& v) noexcept
{
    return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

[[nodiscard]] inline tps::f32 length(vector3df const& v) noexcept
{
    return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

[[nodiscard]] inline tps::f32 length(vector2df const& v) noexcept
{
    return std::sqrt((v.x * v.x) + (v.y * v.y));
}

[[nodiscard]] inline vector4df normalize(vector4df const& v) noexcept
{
    return v / length(v);
}

[[nodiscard]] inline vector3df normalize(vector3df const& v) noexcept
{
    return v / length(v);
}

[[nodiscard]] inline vector2df normalize(vector2df const& v) noexcept
{
    return v / length(v);
}

[[nodiscard]] inline vector3df cross(vector3df const& a,
                                     vector3df const& b) noexcept
{
    return vector3df{(a.y * b.z) - (b.y * a.z), (a.z * b.x) - (b.z * a.x),
                     (a.x * b.y) - (b.x * a.y)};
}

[[nodiscard]] inline vector4df cross(vector4df const& a,
                                     vector4df const& b) noexcept
{
    return vector4df{cross(vector3df{a.x, a.y, a.z}, vector3df{b.x, b.y, b.z})};
}

[[nodiscard]] inline vector2df cross(vector2df const& a,
                                     vector2df const& b) noexcept
{
    auto const temp{cross(vector3df{a}, vector3df{b})};
    return vector2df{temp.x, temp.y};
}

[[nodiscard]] inline tps::f32 dot(vector4df const& a,
                                  vector4df const& b) noexcept
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

[[nodiscard]] inline tps::f32 dot(vector3df const& a,
                                  vector3df const& b) noexcept
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

[[nodiscard]] inline tps::f32 dot(vector2df const& a,
                                   vector2df const& b) noexcept
{
    return ((a.x * b.x) + (a.y * b.y));
}

}  // namespace fmath

#endif
