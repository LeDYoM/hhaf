#pragma once

#ifndef HAF_SCENE_MATRIX4X4_INCLUDE_HPP
#define HAF_SCENE_MATRIX4X4_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace haf::scene
{
class Matrix4x4 final
{
public:
    using Scalar = mtps::f32;

    static constexpr Scalar One  = 1.0F;
    static constexpr Scalar Zero = 0.0F;

    constexpr Matrix4x4() noexcept :
        matrix_data_{One,  Zero, Zero, Zero, Zero, One,  Zero, Zero,
                     Zero, Zero, One,  Zero, Zero, Zero, Zero, One}
    {}

    constexpr Matrix4x4(Scalar const a00,
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

    constexpr Matrix4x4(Matrix4x4 const&) noexcept = default;
    Matrix4x4& operator=(Matrix4x4 const&) noexcept = default;

    constexpr Matrix4x4(Matrix4x4&&) noexcept = default;
    Matrix4x4& operator=(Matrix4x4&&) noexcept = default;

    constexpr mtps::rptr<Scalar const> const getMatrix() const noexcept
    {
        return matrix_data_;
    }

    static Matrix4x4 const Identity;

    Matrix4x4& operator*=(Matrix4x4 const& right) noexcept;
    Matrix4x4 operator*(Matrix4x4 const& right) const noexcept;

private:
    Scalar matrix_data_[16U];
};
}  // namespace haf::scene

#endif
