FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_MATRIX4X4_INCLUDE_HPP
#define FACIL_MATH_MATRIX4X4_INCLUDE_HPP

#include <facil_math/include/math_types.hpp>

#include <cmath>
#include <cfloat>

namespace fmath
{
namespace tps = htps;
/**
 * @brief Type representing a 4x4 matrix.
 * Used to perform operations on the engine
 */
class Matrix4x4 final
{
public:
    static constexpr tps::u32 kNumElements{16U};

    /**
     * @brief Type of the elements internal data
     */
    using Scalar = tps::f32;

    using value_type = Scalar;

    using iterator       = tps::rptr<Scalar>;
    using const_iterator = tps::rptr<Scalar const>;

    /**
     * @brief Value "1" for the elements of this matrix
     */
    static constexpr Scalar const One{One<Scalar>};

    /**
     * @brief Value "0" for the elements of this matrix
     */
    static constexpr Scalar const Zero{Zero<Scalar>};

    constexpr Matrix4x4() noexcept :
        m_matrix_data{One,  Zero, Zero, Zero, Zero, One,  Zero, Zero,
                      Zero, Zero, One,  Zero, Zero, Zero, Zero, One}
    {}

    constexpr Matrix4x4(Scalar const a00,
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

    constexpr void setIdentity() noexcept
    {
        for (int i{0}; i < static_cast<int>(kMatrixNumElements); ++i)
        {
            m_matrix_data[i] = ((i % 5) == 0) ? One : Zero;
        }
    }

    constexpr tps::rptr<Scalar const> getMatrix() const noexcept
    {
        return m_matrix_data;
    }

    template <tps::u32 column>
    constexpr void setColumn(Scalar vx, Scalar vy, Scalar vz, Scalar vw)
    {
        static_assert(column < 4U, "Column must be smaller that 4");
        constexpr tps::u32 startPoint{column * 4U};
        m_matrix_data[0U + startPoint] = vx;
        m_matrix_data[1U + startPoint] = vy;
        m_matrix_data[2U + startPoint] = vz;
        m_matrix_data[3U + startPoint] = vw;
    }

    template <tps::u32 column>
    constexpr void setColumn(fmath::vector4d<Scalar> v)
    {
        setColumn<column>(v.x, v.y, v.z, v.w);
    }

    template <tps::u32 column>
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

    template <tps::u32 column>
    constexpr void setColumn(fmath::vector3d<Scalar> v)
    {
        setColumn<column>(v.x, v.y, v.z);
    }

    constexpr void setDiagonal(fmath::vector4d<Scalar> const& v) noexcept
    {
        m_matrix_data[0]  = v.x;
        m_matrix_data[5]  = v.y;
        m_matrix_data[10] = v.z;
        m_matrix_data[15] = v.w;
    }

    constexpr void setDiagonal(fmath::vector3d<Scalar> const& v) noexcept
    {
        setDiagonal({v.x, v.y, v.z, One});
    }

    constexpr Scalar operator[](int32_t const index) const noexcept
    {
        return m_matrix_data[index];
    }

    constexpr Scalar& operator[](int32_t const index) noexcept
    {
        return m_matrix_data[index];
    }

    static Matrix4x4 const Identity;

    constexpr Matrix4x4& operator*=(Matrix4x4 const& rhs) noexcept
    {
        auto const m{getMatrix()};
        auto const n{rhs.getMatrix()};

        return *this = Matrix4x4{
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

    constexpr vector4d<Scalar> operator*(vector4d<Scalar> const& rhs) noexcept
    {
        auto const m{getMatrix()};

        return vector4df{
            m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z + m[12] * rhs.w,
            m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z + m[13] * rhs.w,
            m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z + m[14] * rhs.w,
            m[3] * rhs.x + m[7] * rhs.y + m[11] * rhs.z + m[15] * rhs.w};
    }

    constexpr vector3d<Scalar> operator*(vector3d<Scalar> const& rhs) noexcept
    {
        auto result{*this * vector4d<Scalar>{rhs.x, rhs.y, rhs.z, One}};
        return {result.x, result.y, result.z};
    }

    constexpr vector2d<Scalar> operator*(vector2d<Scalar> const& rhs) noexcept
    {
        auto result{*this * vector4d<Scalar>{rhs.x, rhs.y, Zero, One}};
        return {result.x, result.y};
    }

    constexpr iterator begin() noexcept { return m_matrix_data; }
    constexpr const_iterator begin() const noexcept { return m_matrix_data; }
    constexpr const_iterator cbegin() const noexcept { return m_matrix_data; }
    constexpr iterator end() noexcept
    {
        return &m_matrix_data[kMatrixNumElements];
    }

    constexpr const_iterator end() const noexcept
    {
        return &m_matrix_data[kMatrixNumElements];
    }

    constexpr const_iterator cend() const noexcept
    {
        return &m_matrix_data[kMatrixNumElements];
    }

    static constexpr Matrix4x4 translatelationMatrix(
        vector3d<Scalar> const& pos)
    {
        return Matrix4x4{OneF32,  ZeroF32, ZeroF32, ZeroF32, ZeroF32, OneF32,
                         ZeroF32, ZeroF32, ZeroF32, ZeroF32, OneF32,  ZeroF32,
                         pos.x,   pos.y,   pos.z,   OneF32};
    }

    constexpr void translate(vector3d<Scalar> const& pos)
    {
        *this *= translatelationMatrix(pos);
    }

    static constexpr Matrix4x4 scaleMatrix(vector3d<Scalar> const& scale)
    {
        return Matrix4x4{scale.x, ZeroF32, ZeroF32, ZeroF32, ZeroF32, scale.y,
                         ZeroF32, ZeroF32, ZeroF32, ZeroF32, scale.z, ZeroF32,
                         ZeroF32, ZeroF32, ZeroF32, OneF32};
    }

    static constexpr Matrix4x4 scaleMatrix(Scalar scale)
    {
        return scaleMatrix(vector3d{scale, scale, scale});
    }

    constexpr void scale(vector3d<Scalar> const& pos)
    {
        *this *= scaleMatrix(pos);
    }

    constexpr void scale(Scalar pos) { *this *= scaleMatrix(pos); }

    static constexpr tps::size_type const kMatrixNumElements{16U};

private:
    Scalar m_matrix_data[kMatrixNumElements];
};

inline Matrix4x4 const Matrix4x4::Identity{Matrix4x4{}};

constexpr void setDiagonal(Matrix4x4& m,
                           fmath::vector4d<Matrix4x4::Scalar> const& v) noexcept
{
    m.setDiagonal(v);
}

constexpr void setDiagonal(Matrix4x4& m,
                           fmath::vector3d<Matrix4x4::Scalar> const& v) noexcept
{
    setDiagonal(m, {v.x, v.y, v.z, Matrix4x4::One});
}

[[nodiscard]] constexpr Matrix4x4 operator*(Matrix4x4 const& lhs,
                                            Matrix4x4 const& rhs) noexcept
{
    return Matrix4x4{lhs} *= rhs;
}

constexpr bool operator==(Matrix4x4 const& lhs, Matrix4x4 const& rhs) noexcept
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

[[nodiscard]] inline bool isAlmostEqual(tps::f32 const lhs,
                                        tps::f32 const rhs) noexcept
{
    return std::fabs(lhs - rhs) < FLT_EPSILON;
}

[[nodiscard]] inline bool isAlmostEqual(vector3df const lhs,
                                        vector3df const rhs) noexcept
{
    return isAlmostEqual(lhs.x, rhs.x) && isAlmostEqual(lhs.y, rhs.y) &&
        isAlmostEqual(lhs.z, rhs.z);
}

[[nodiscard]] constexpr bool isAlmostEqual(Matrix4x4 const& lhs,
                                           Matrix4x4 const& rhs) noexcept
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
}  // namespace fmath

#endif
