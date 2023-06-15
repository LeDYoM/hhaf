#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/core/geometry_math.hpp>

#include <cmath>
#include <cfloat>

using namespace haf::core;
using namespace fmath;

namespace haf::math
{

Matrix4x4::Matrix4x4() noexcept :
    m_matrix_data{One,  Zero, Zero, Zero, Zero, One,  Zero, Zero,
                  Zero, Zero, One,  Zero, Zero, Zero, Zero, One}
{}

Matrix4x4::Matrix4x4(Scalar const a00,
                     Scalar const a01,
                     Scalar const a02,
                     Scalar const a03,
                     Scalar const a10,
                     Scalar const a11,
                     Scalar const a12,
                     Scalar const a13,
                     Scalar const a20,
                     Scalar const a21,
                     Scalar const a22,
                     Scalar const a23,
                     Scalar const a30,
                     Scalar const a31,
                     Scalar const a32,
                     Scalar const a33) noexcept :
    m_matrix_data{a00, a01, a02, a03, a10, a11, a12, a13,
                  a20, a21, a22, a23, a30, a31, a32, a33}

{}

void Matrix4x4::setIdentity() noexcept
{
    for (int i{0}; i < static_cast<int>(kMatrixNumElements); ++i)
    {
        m_matrix_data[i] = ((i % 5) == 0) ? One : Zero;
    }
}

const Matrix4x4 Matrix4x4::Identity = Matrix4x4{};

void Matrix4x4::setDiagonal(fmath::vector3d<Scalar> const& v) noexcept
{
    setDiagonal({v.x, v.y, v.z, One});
}

void Matrix4x4::setDiagonal(fmath::vector4d<Scalar> const& v) noexcept
{
    m_matrix_data[0]  = v.x;
    m_matrix_data[5]  = v.y;
    m_matrix_data[10] = v.z;
    m_matrix_data[15] = v.w;
}

Matrix4x4& Matrix4x4::operator*=(Matrix4x4 const& transform) noexcept
{
    return *this = (*this * transform);
}

Matrix4x4::iterator Matrix4x4::begin() noexcept
{
    return m_matrix_data;
}

Matrix4x4::const_iterator Matrix4x4::begin() const noexcept
{
    return m_matrix_data;
}

Matrix4x4::const_iterator Matrix4x4::cbegin() const noexcept
{
    return m_matrix_data;
}

Matrix4x4::iterator Matrix4x4::end() noexcept
{
    return &m_matrix_data[kMatrixNumElements];
}

Matrix4x4::const_iterator Matrix4x4::end() const noexcept
{
    return &m_matrix_data[kMatrixNumElements];
}

Matrix4x4::const_iterator Matrix4x4::cend() const noexcept
{
    return &m_matrix_data[kMatrixNumElements];
}

Matrix4x4 operator*(Matrix4x4 const& lhs, Matrix4x4 const& rhs) noexcept
{
    auto const m{lhs.getMatrix()};
    auto const n{rhs.getMatrix()};

    return Matrix4x4{
        m[0] * n[0] + m[4] * n[1] + m[8] * n[2] + m[12] * n[3],
        m[1] * n[0] + m[5] * n[1] + m[9] * n[2] + m[13] * n[3],
        m[2] * n[0] + m[6] * n[1] + m[10] * n[2] + m[14] * n[3],
        m[3] * n[0] + m[7] * n[1] + m[11] * n[2] + m[15] * n[3],
        m[0] * n[4] + m[4] * n[5] + m[8] * n[6] + m[12] * n[7],
        m[1] * n[4] + m[5] * n[5] + m[9] * n[6] + m[13] * n[7],
        m[2] * n[4] + m[6] * n[5] + m[10] * n[6] + m[14] * n[7],
        m[3] * n[4] + m[7] * n[5] + m[11] * n[6] + m[15] * n[7],
        m[0] * n[8] + m[4] * n[9] + m[8] * n[10] + m[12] * n[11],
        m[1] * n[8] + m[5] * n[9] + m[9] * n[10] + m[13] * n[11],
        m[2] * n[8] + m[6] * n[9] + m[10] * n[10] + m[14] * n[11],
        m[3] * n[8] + m[7] * n[9] + m[11] * n[10] + m[15] * n[11],
        m[0] * n[12] + m[4] * n[13] + m[8] * n[14] + m[12] * n[15],
        m[1] * n[12] + m[5] * n[13] + m[9] * n[14] + m[13] * n[15],
        m[2] * n[12] + m[6] * n[13] + m[10] * n[14] + m[14] * n[15],
        m[3] * n[12] + m[7] * n[13] + m[11] * n[14] + m[15] * n[15]};
}

bool operator==(Matrix4x4 const& lhs, Matrix4x4 const& rhs) noexcept
{
    for (auto lhs_ci{lhs.cbegin()}, rhs_ci{rhs.cbegin()};
         lhs_ci != lhs.cend() && rhs_ci != rhs.cend(); ++lhs_ci, ++rhs_ci)
    {
        if (*lhs_ci != *rhs_ci)
        {
            return false;
        }
    }
    return true;
}

namespace
{
bool isAlmostEqual(htps::f32 const lhs, htps::f32 const rhs) noexcept
{
    return std::fabsf(lhs - rhs) < FLT_EPSILON;
}
}  // namespace

bool isAlmostEqual(Matrix4x4 const& lhs, Matrix4x4 const& rhs) noexcept
{
    for (auto lhs_ci{lhs.cbegin()}, rhs_ci{rhs.cbegin()};
         lhs_ci != lhs.cend() && rhs_ci != rhs.cend(); ++lhs_ci, ++rhs_ci)
    {
        if (!isAlmostEqual(*lhs_ci, *rhs_ci))
        {
            return false;
        }
    }
    return true;
}

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
