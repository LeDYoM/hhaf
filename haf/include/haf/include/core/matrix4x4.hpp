HTPS_PRAGMA_ONCE
#ifndef HAF_TYPES_MATRIX4X4_INCLUDE_HPP
#define HAF_TYPES_MATRIX4X4_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/core/math_types.hpp>
#include <htypes/include/array.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::math
{
/**
 * @brief Type representing a 4x4 matrix.
 * Used to perform operations on the engine
 */
class HAF__API Matrix4x4 final
{
public:
    static constexpr core::u32 kNumElements{16U};

    /**
     * @brief Type of the elements internal data
     */
    using Scalar = core::f32;

    using iterator       = core::rptr<Scalar>;
    using const_iterator = core::rptr<Scalar const>;

    /**
     * @brief Value "0" for the elements of this matrix
     */
    static constexpr Scalar const One{haf::One<Scalar>};

    /**
     * @brief Value "1" for the elements of this matrix
     */
    static constexpr Scalar const Zero{haf::Zero<Scalar>};

    Matrix4x4() noexcept;

    Matrix4x4(Scalar const a00,
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
              Scalar const a33) noexcept;

    void setIdentity() noexcept;

    constexpr htps::rptr<Scalar const> getMatrix() const noexcept
    {
        return m_matrix_data;
    }

    template <core::u32 column>
    constexpr void setColumn(Scalar vx, Scalar vy, Scalar vz, Scalar vw)
    {
        static_assert(column < 4U, "Column must be smaller that 4");
        constexpr core::u32 startPoint{column * 4U};
        m_matrix_data[0U + startPoint]  = vx;
        m_matrix_data[1U + startPoint]  = vy;
        m_matrix_data[2U + startPoint]  = vz;
        m_matrix_data[3U + startPoint] = vw;
    }

    template <core::u32 column>
    constexpr void setColumn(core::vector4d<Scalar> v)
    {
        setColumn<column>(v.x, v.y, v.z, v.w);
    }

    template <core::u32 column>
    constexpr void setColumn(Scalar vx, Scalar vy, Scalar vz)
    {
        static_assert(column < 4U, "Column must be smaller that 4");

        if constexpr (column == 0U)
        {
            setColumn<column>(One, vx, vy, vz);
        }
        else if constexpr (column == 1U)
        {
            setColumn<column>(vx, One, vy, vz);
        }
        else if constexpr (column == 2U)
        {
            setColumn<column>(vx, vy, One, vz);
        }
        else if constexpr (column == 3U)
        {
            setColumn<column>(vx, vy, vz, One);
        }
    }

    template <core::u32 column>
    constexpr void setColumn(core::vector3d<Scalar> v)
    {
        setColumn<column>(v.x, v.y, v.z);
    }

    void setDiagonal(core::vector3d<Scalar> const& v) noexcept;
    void setDiagonal(core::vector4d<Scalar> const& v) noexcept;
    void setRotation(core::vector3d<Scalar> const& v,
                     Scalar const angle) noexcept;

    void setRotation(Scalar const x,
                     Scalar const y,
                     Scalar const z,
                     Scalar const angle) noexcept;

    static Matrix4x4 const Identity;

    Matrix4x4& operator*=(Matrix4x4 const& right) noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    static constexpr const core::size_type kMatrixNumElements{16U};

private:
    Scalar m_matrix_data[kMatrixNumElements];
};

[[nodiscard]] Matrix4x4 operator*(Matrix4x4 const& lhs,
                                  Matrix4x4 const& rhs) noexcept;
bool operator==(Matrix4x4 const& lhs, Matrix4x4 const& rhs) noexcept;
[[nodiscard]] bool isAlmostEqual(Matrix4x4 const& lhs,
                                 Matrix4x4 const& rhs) noexcept;

[[nodiscard]] Matrix4x4 lookat(core::vector3df const& eye,
                               core::vector3df const& center,
                               core::vector3df const& up);
[[nodiscard]] Matrix4x4 frustum(core::f32 const left,
                                core::f32 const right,
                                core::f32 const bottom,
                                core::f32 const top,
                                core::f32 const n,
                                core::f32 const f);
[[nodiscard]] Matrix4x4 perspective(core::f32 fovy,
                                    core::f32 const aspect,
                                    core::f32 const n,
                                    core::f32 const f);

[[nodiscard]] Matrix4x4 ortho(core::f32 const left,
                              core::f32 const right,
                              core::f32 const bottom,
                              core::f32 const top,
                              core::f32 const n,
                              core::f32 const f);

}  // namespace haf::math

#endif
