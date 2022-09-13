HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_MATRIX4X4_INCLUDE_HPP
#define HAF_SCENE_MATRIX4X4_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/array.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::scene
{
/**
 * @brief Type representing a 4x4 matrix.
 * Used to perform operations on the engine
 */
class HAF__API Matrix4x4 final
{
public:
    /**
     * @brief Type of the elements internal data
     */
    using Scalar = htps::f32;

    /**
     * @brief Value "0" for the elements of this matrix
     */
    static constexpr Scalar const One = static_cast<Scalar>(1.0);

    /**
     * @brief Value "1" for the elements of this matrix
     */
    static constexpr Scalar const Zero = static_cast<Scalar>(0.0);

    Matrix4x4() noexcept;

    Matrix4x4(Scalar const a00,
              Scalar const a01,
              Scalar const a02,
              Scalar const a10,
              Scalar const a11,
              Scalar const a12,
              Scalar const a20,
              Scalar const a21,
              Scalar const a22) noexcept;

    constexpr htps::rptr<Scalar const> getMatrix() const noexcept
    {
        return matrix_data_;
    }

    static Matrix4x4 const Identity;

    Matrix4x4& operator*=(Matrix4x4 const& right) noexcept;

private:
    Scalar matrix_data_[16U];
};

Matrix4x4 operator*(Matrix4x4 const& lhs, Matrix4x4 const& rhs) noexcept;

}  // namespace haf::scene

#endif
