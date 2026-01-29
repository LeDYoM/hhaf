module;

#include <cmath>

export module facil_math:geometry_math;

import :math_types;
import :vector_types;
import :rect;

namespace fmath
{
export template <typename T>
constexpr T PiConstant = static_cast<T>(3.14159265358979323846);

export template <typename T>
constexpr T PiD2Constant = PiConstant<T> / static_cast<T>(2);

export template <typename T>
constexpr T PiM2Constant = PiConstant<T>* static_cast<T>(2);

export template <typename T>
constexpr T PiMDConstant = PiConstant<T>* static_cast<T>(1.5);

export template <typename T>
constexpr T ToRadians = PiConstant<T> / static_cast<T>(180);

export [[nodiscard]] inline tps::f32 length(vector4df const& v) noexcept
{
    return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

export [[nodiscard]] inline tps::f32 length(vector3df const& v) noexcept
{
    return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

export [[nodiscard]] inline tps::f32 length(vector2df const& v) noexcept
{
    return std::sqrt((v.x * v.x) + (v.y * v.y));
}

export [[nodiscard]] inline vector4df normalize(vector4df const& v) noexcept
{
    return v / length(v);
}

export [[nodiscard]] inline vector3df normalize(vector3df const& v) noexcept
{
    return v / length(v);
}

export [[nodiscard]] inline vector2df normalize(vector2df const& v) noexcept
{
    return v / length(v);
}

export [[nodiscard]] inline vector3df cross(vector3df const& a,
                                     vector3df const& b) noexcept
{
    return vector3df{(a.y * b.z) - (b.y * a.z), (a.z * b.x) - (b.z * a.x),
                     (a.x * b.y) - (b.x * a.y)};
}

export [[nodiscard]] inline vector4df cross(vector4df const& a,
                                     vector4df const& b) noexcept
{
    return vector4df{cross(vector3df{a.x, a.y, a.z}, vector3df{b.x, b.y, b.z})};
}

export [[nodiscard]] inline vector2df cross(vector2df const& a,
                                     vector2df const& b) noexcept
{
    auto const temp{cross(vector3df{a}, vector3df{b})};
    return vector2df{temp.x, temp.y};
}

export [[nodiscard]] inline tps::f32 dot(vector4df const& a,
                                  vector4df const& b) noexcept
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

export [[nodiscard]] inline tps::f32 dot(vector3df const& a,
                                  vector3df const& b) noexcept
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

export [[nodiscard]] inline tps::f32 dot(vector2df const& a,
                                  vector2df const& b) noexcept
{
    return ((a.x * b.x) + (a.y * b.y));
}

}  // namespace fmath
