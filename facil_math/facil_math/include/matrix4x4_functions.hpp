FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_MATRIX4X4_FUNCTIONS_INCLUDE_HPP
#define FACIL_MATH_MATRIX4X4_FUNCTIONS_INCLUDE_HPP

#include <facil_math/include/math_types.hpp>
#include <facil_math/include/matrix4x4.hpp>

#include <cmath>
#include <cfloat>

namespace fmath
{
[[nodiscard]] inline Matrix4x4 lookat(vector3df const& eye,
                                      vector3df const& center,
                                      vector3df const& up) noexcept
{
    const auto forward{normalize(center - eye)};
    const auto up_normalized{normalize(up)};
    const auto sideways{cross(forward, up_normalized)};
    const auto u{cross(sideways, forward)};

    auto M = Matrix4x4{sideways.x, u.x,  -forward.x, 0.0F, sideways.y, u.y,
                       -forward.y, 0.0F, sideways.z, u.z,  -forward.z, 0.0F,
                       0.0F,       0.0F, 0.0F,       1.0F};

    return M * Matrix4x4{OneF32,  ZeroF32, ZeroF32, ZeroF32, ZeroF32, OneF32,
                         ZeroF32, ZeroF32, ZeroF32, ZeroF32, OneF32,  ZeroF32,
                         -eye.x,  -eye.y,  -eye.z,  OneF32};
}

[[nodiscard]] inline Matrix4x4 frustum(tps::f32 const left,
                                       tps::f32 const right,
                                       tps::f32 const bottom,
                                       tps::f32 const top,
                                       tps::f32 const n,
                                       tps::f32 const f) noexcept
{
    if ((right == left) || (top == bottom) || (n == f) || (n < 0.0F) ||
        (f < 0.0F))
    {
        return Matrix4x4::Identity;
    }

    return {(2.0F * n) / (right - left),
            ZeroF32,
            ZeroF32,
            ZeroF32,

            ZeroF32,
            (2.0F * n) / (top - bottom),
            ZeroF32,
            ZeroF32,

            ((right + left) / (right - left)),
            ((top + bottom) / (top - bottom)),
            (-(f + n) / (f - n)),
            -OneF32,

            ZeroF32,
            ZeroF32,
            (-2.0F * f * n) / (f - n),
            ZeroF32};
}

[[nodiscard]] inline Matrix4x4 perspective(tps::f32 fovy,
                                           tps::f32 const aspect,
                                           tps::f32 const n,
                                           tps::f32 const f) noexcept
{
    const tps::f32 q{1.0F / std::tan(ToRadians<tps::f32> * (0.5F * fovy))};
    const tps::f32 A{q / aspect};
    const tps::f32 B{(n + f) / (n - f)};
    const tps::f32 C{(2.0F * n * f) / (n - f)};

    return {A,       ZeroF32, ZeroF32, ZeroF32, ZeroF32, q,
            ZeroF32, ZeroF32, ZeroF32, ZeroF32, B,       -1.0F,
            ZeroF32, ZeroF32, C,       ZeroF32};
}

[[nodiscard]] inline Matrix4x4 ortho(tps::f32 const left,
                                     tps::f32 const right,
                                     tps::f32 const bottom,
                                     tps::f32 const top,
                                     tps::f32 const n,
                                     tps::f32 const f) noexcept
{
    return {2.0F / (right - left),
            0.0F,
            0.0F,
            0.0F,

            0.0F,
            2.0F / (top - bottom),
            0.0F,
            0.0F,

            0.0F,
            0.0F,
            2.0F / (n - f),
            0.0F,

            (left + right) / (left - right),
            (bottom + top) / (bottom - top),
            (n + f) / (f - n),
            1.0F};
}

}  // namespace fmath

#endif
