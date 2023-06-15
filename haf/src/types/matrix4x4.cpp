#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/core/geometry_math.hpp>

using namespace haf::core;
using namespace fmath;

namespace haf::math
{

Matrix4x4 lookat(vector3df const& eye,
                 vector3df const& center,
                 vector3df const& up)
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

Matrix4x4 frustum(f32 const left,
                  f32 const right,
                  f32 const bottom,
                  f32 const top,
                  f32 const n,
                  f32 const f)
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

Matrix4x4 perspective(f32 fovy, f32 const aspect, f32 const n, f32 const f)
{
    const f32 q{1.0F / std::tan(ToRadians<f32> * (0.5F * fovy))};
    const f32 A{q / aspect};
    const f32 B{(n + f) / (n - f)};
    const f32 C{(2.0F * n * f) / (n - f)};

    return {A,       ZeroF32, ZeroF32, ZeroF32, ZeroF32, q,
            ZeroF32, ZeroF32, ZeroF32, ZeroF32, B,       -1.0F,
            ZeroF32, ZeroF32, C,       ZeroF32};
}

Matrix4x4 ortho(f32 const left,
                 f32 const right,
                 f32 const bottom,
                 f32 const top,
                 f32 const n,
                 f32 const f)
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
/*
Matrix4x4 ortho(f32 const left,
                f32 const right,
                f32 const bottom,
                f32 const top,
                f32 const n,
                f32 const f)
{
    Matrix4x4 m1{ortho_v(left, right, bottom, top, n, f)};
    Matrix4x4 m2{ortho_(left, right, bottom, top, n, f)};
    if (!isAlmostEqual(m1, m2))
    {
        int b = 0;
        (void)(b);
    }
    return m1;
}
*/

}  // namespace haf::math
