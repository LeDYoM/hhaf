#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/core/geometry_math.hpp>

#include <limits>
#include <cmath>

#include "vmath.h"

using namespace haf::core;

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
    for (int i{0}; i < 16; ++i)
    {
        m_matrix_data[i] = ((i % 5) == 0) ? One : Zero;
    }
}

const Matrix4x4 Matrix4x4::Identity = Matrix4x4{};

void Matrix4x4::setDiagonal(core::vector3d<Scalar> const& v) noexcept
{
    setDiagonal({v.x, v.y, v.z, One});
}

void Matrix4x4::setDiagonal(core::vector4d<Scalar> const& v) noexcept
{
    m_matrix_data[0]  = v.x;
    m_matrix_data[5]  = v.y;
    m_matrix_data[10] = v.z;
    m_matrix_data[15] = v.w;
}

void Matrix4x4::setRotation(core::vector3d<Scalar> const& v,
                            Scalar const angle) noexcept
{
    setRotation(v.x, v.y, v.z, angle);
}

void Matrix4x4::setRotation(Scalar const x,
                            Scalar const y,
                            Scalar const z,
                            Scalar const angle) noexcept
{
    Scalar const c{std::cos(angle * ToRadians<Scalar>)};
    Scalar const s{std::sin(angle * ToRadians<Scalar>)};
    Scalar const c1{One - c};
    Scalar const m0{m_matrix_data[0]}, m4{m_matrix_data[4]},
        m8{m_matrix_data[8]}, m12{m_matrix_data[12]}, m1{m_matrix_data[1]},
        m5{m_matrix_data[5]}, m9{m_matrix_data[9]}, m13{m_matrix_data[13]},
        m2{m_matrix_data[2]}, m6{m_matrix_data[6]}, m10{m_matrix_data[10]},
        m14{m_matrix_data[14]};

    // build rotation matrix
    Scalar const r0{(x * x * c1) + c};
    Scalar const r1{(x * y * c1) + (z * s)};
    Scalar const r2{(x * z * c1) - (y * s)};
    Scalar const r4{(x * y * c1) - (z * s)};
    Scalar const r5{(y * y * c1) + c};
    Scalar const r6{(y * z * c1) + (x * s)};
    Scalar const r8{(x * z * c1) + (y * s)};
    Scalar const r9{(y * z * c1) - (x * s)};
    Scalar const r10{(z * z * c1) + c};

    // multiply rotation matrix
    m_matrix_data[0]  = (r0 * m0) + (r4 * m1) + (r8 * m2);
    m_matrix_data[1]  = (r1 * m0) + (r5 * m1) + (r9 * m2);
    m_matrix_data[2]  = (r2 * m0) + (r6 * m1) + (r10 * m2);
    m_matrix_data[4]  = (r0 * m4) + (r4 * m5) + (r8 * m6);
    m_matrix_data[5]  = (r1 * m4) + (r5 * m5) + (r9 * m6);
    m_matrix_data[6]  = (r2 * m4) + (r6 * m5) + (r10 * m6);
    m_matrix_data[8]  = (r0 * m8) + (r4 * m9) + (r8 * m10);
    m_matrix_data[9]  = (r1 * m8) + (r5 * m9) + (r9 * m10);
    m_matrix_data[10] = (r2 * m8) + (r6 * m9) + (r10 * m10);
    m_matrix_data[12] = (r0 * m12) + (r4 * m13) + (r8 * m14);
    m_matrix_data[13] = (r1 * m12) + (r5 * m13) + (r9 * m14);
    m_matrix_data[14] = (r2 * m12) + (r6 * m13) + (r10 * m14);
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
    return std::abs(lhs - rhs) < std::numeric_limits<htps::f32>::epsilon();
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
/*
Matrix4x4 lookat(vector3df const& eye,
                 vector3df const& center,
                 vector3df const& up)
{
    auto const forward_vector{normalize(center - eye)};
    auto const sideways_vector{normalize(cross(forward_vector, up))};
    auto const up_camera_vector{cross(sideways_vector, forward_vector)};

    Matrix4x4 temp{sideways_vector.x,
                   sideways_vector.y,
                   sideways_vector.z,
                   Zero<f32>,

                   up_camera_vector.x,
                   up_camera_vector.y,
                   up_camera_vector.z,
                   Zero<f32>,

                   -forward_vector.x,
                   -forward_vector.y,
                   -forward_vector.z,
                   Zero<f32>,

                   ZeroF32,
                   ZeroF32,
                   ZeroF32,
                   OneF32};

    Matrix4x4 translated{OneF32,  ZeroF32, ZeroF32, ZeroF32, ZeroF32, OneF32,
                         ZeroF32, ZeroF32, ZeroF32, ZeroF32, OneF32,  ZeroF32,
                         -eye.x,  -eye.y,  -eye.z,  OneF32};
    return temp * translated;
}
*/
Matrix4x4 toMatrix(vmath::mat4 const& m)
{
    return Matrix4x4{
        m[0][0], m[0][1], m[0][2], m[0][3],
        m[1][0], m[1][1], m[1][2], m[1][3],
        m[2][0], m[2][1], m[2][2], m[2][3],
        m[3][0], m[3][1], m[3][2], m[3][3]};
}

Matrix4x4 lookat(vector3df const& eye,
                 vector3df const& center,
                 vector3df const& up)
{
    vmath::vec3 _eye{eye.x, eye.y, eye.z};
    vmath::vec3 _center{center.x, center.y, center.z};
    vmath::vec3 _up{up.x, up.y, up.z};
    auto result = vmath::lookat(_eye, _center, _up);
    return toMatrix(result);
}

/*
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
*/

Matrix4x4 frustum(f32 const left,
                  f32 const right,
                  f32 const bottom,
                  f32 const top,
                  f32 const n,
                  f32 const f)
{
    auto result = vmath::frustum(left, right, bottom, top, n, f);
    return toMatrix(result);
}

Matrix4x4 perspective(f32 fovy, f32 const aspect, f32 const n, f32 const f)
{
    auto result = vmath::perspective(fovy, aspect, n, f);
    return toMatrix(result);
}

/*
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
*/
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

}  // namespace haf::math
