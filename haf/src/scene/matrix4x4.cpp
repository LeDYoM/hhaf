#include <haf/include/scene/matrix4x4.hpp>

namespace haf::scene
{

Matrix4x4::Matrix4x4() noexcept :
    matrix_data_{One,  Zero, Zero, Zero, Zero, One,  Zero, Zero,
                 Zero, Zero, One,  Zero, Zero, Zero, Zero, One}
{}

Matrix4x4::Matrix4x4(Scalar const a00,
                     Scalar const a01,
                     Scalar const a02,
                     Scalar const a10,
                     Scalar const a11,
                     Scalar const a12,
                     Scalar const a20,
                     Scalar const a21,
                     Scalar const a22) noexcept :
    matrix_data_{a00,  a10,  Zero, a20,  a01, a11, Zero, a21,
                 Zero, Zero, One,  Zero, a02, a12, Zero, a22}
{}

const Matrix4x4 Matrix4x4::Identity = Matrix4x4{};

Matrix4x4& Matrix4x4::operator*=(Matrix4x4 const& transform) noexcept
{
    return *this = (*this * transform);
}

Matrix4x4 operator*(Matrix4x4 const& lhs, Matrix4x4 const& rhs) noexcept
{
    auto const a{lhs.getMatrix()};
    auto const b{rhs.getMatrix()};

    return {(a[0U] * b[0U]) + (a[4U] * b[1U]) + (a[12U] * b[3U]),
            (a[0U] * b[4U]) + (a[4U] * b[5U]) + (a[12U] * b[7U]),
            (a[0U] * b[12U]) + (a[4U] * b[13U]) + (a[12U] * b[15U]),
            (a[1U] * b[0U]) + (a[5U] * b[1U]) + (a[13U] * b[3U]),
            (a[1U] * b[4U]) + (a[5U] * b[5U]) + (a[13U] * b[7U]),
            (a[1U] * b[12U]) + (a[5U] * b[13U]) + (a[13U] * b[15U]),
            (a[3U] * b[0U]) + (a[7U] * b[1U]) + (a[15U] * b[3U]),
            (a[3U] * b[4U]) + (a[7U] * b[5U]) + (a[15U] * b[7U]),
            (a[3U] * b[12U]) + (a[7U] * b[13U]) + (a[15U] * b[15U])};
}

}  // namespace haf::scene
