#pragma once

#ifndef HAF_TRANSFORMATION_INCLUDE_HPP
#define HAF_TRANSFORMATION_INCLUDE_HPP

#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>

namespace haf::scene
{
class Transform final
{
public:
    using Scalar = mtps::f32;
    using VectorScalar = mtps::vector2d<Scalar>;
    using RectScalar = mtps::Rect<Scalar>;

    static constexpr Scalar One = 1.0F;
    static constexpr Scalar Zero = 0.0F;
    constexpr Transform() noexcept
        : m_matrix{One, Zero, Zero, Zero,
                   Zero, One, Zero, Zero,
                   Zero, Zero, One, Zero,
                   Zero, Zero, Zero, One} {}

    constexpr Transform(const Scalar a00, const Scalar a01, const Scalar a02,
                        const Scalar a10, const Scalar a11, const Scalar a12,
                        const Scalar a20, const Scalar a21, const Scalar a22) noexcept
        : m_matrix{a00, a10, Zero, a20,
                   a01, a11, Zero, a21,
                   Zero, Zero, One, Zero,
                   a02, a12, Zero, a22} {}

    constexpr Transform(const Transform &) noexcept = default;
    Transform &operator=(const Transform &) noexcept = default;

    constexpr Transform(Transform &&) noexcept = default;
    Transform &operator=(Transform &&) noexcept = default;

    constexpr const Scalar *const getMatrix() const noexcept { return &m_matrix[0U]; }

    static const Transform Identity;

    inline Transform &operator*=(const Transform &right) noexcept
    {
        return combine(right);
    }

    inline Transform operator*(const Transform &right) const noexcept
    {
        Transform copy{*this};
        copy.combine(right);
        return copy;
    }

    inline const VectorScalar operator*(const VectorScalar &right) const noexcept
    {
        return transformPoint(right);
    }

    VectorScalar transformPoint(const Scalar x, const Scalar y) const noexcept;
    VectorScalar transformPoint(const VectorScalar &point) const noexcept;
    RectScalar transformRect(const RectScalar &rectangle) const noexcept;
    Transform &combine(const Transform &transform) noexcept;
    Transform &translate(const Scalar x, const Scalar y) noexcept;
    Transform &translate(const VectorScalar &offset) noexcept;
    Transform &rotate(const Scalar angle) noexcept;
    Transform &rotate(const Scalar angle, const Scalar centerX, const Scalar centerY) noexcept;
    Transform &rotate(const Scalar angle, const VectorScalar &center) noexcept;
    Transform &scale(const Scalar scaleX, const Scalar scaleY) noexcept;
    Transform &scale(const Scalar scaleX, const Scalar scaleY, const Scalar centerX, const Scalar centerY) noexcept;
    Transform &scale(const VectorScalar &factors) noexcept;
    Transform &scale(const VectorScalar &factors, const VectorScalar &center) noexcept;

private:
    Scalar m_matrix[16U];
};
} // namespace haf::scene

#endif
