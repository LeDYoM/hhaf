#pragma once

#ifndef HAF_TRANSFORMN_INCLUDE_HPP
#define HAF_TRANSFORM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>

namespace haf::scene
{
class Transform final
{
public:
    using Scalar       = mtps::f32;
    using VectorScalar = mtps::vector2d<Scalar>;
    using RectScalar   = mtps::Rect<Scalar>;

    static constexpr Scalar One  = 1.0F;
    static constexpr Scalar Zero = 0.0F;

    constexpr Transform() noexcept :
        matrix_data_{One,  Zero, Zero, Zero, Zero, One,  Zero, Zero,
                     Zero, Zero, One,  Zero, Zero, Zero, Zero, One}
    {}

    constexpr Transform(Scalar const a00,
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

    constexpr Transform(const Transform&) noexcept = default;
    Transform& operator=(const Transform&) noexcept = default;

    constexpr Transform(Transform&&) noexcept = default;
    Transform& operator=(Transform&&) noexcept = default;

    constexpr mtps::rptr<Scalar const> const getMatrix() const noexcept
    {
        return matrix_data_;
    }

    static Transform const Identity;

    inline Transform& operator*=(Transform const& right) noexcept
    {
        return combine(right);
    }

    inline Transform operator*(Transform const& right) const noexcept
    {
        Transform copy{*this};
        copy *= right;
        return copy;
    }

    inline const VectorScalar operator*(
        const VectorScalar& right) const noexcept
    {
        return transformPoint(right);
    }

    VectorScalar transformPoint(Scalar const x, Scalar const y) const noexcept;
    VectorScalar transformPoint(VectorScalar const& point) const noexcept;
    RectScalar transformRect(RectScalar const& rectangle) const noexcept;
    Transform& combine(Transform const& transform) noexcept;
    Transform& translate(Scalar const x, Scalar const y) noexcept;
    Transform& translate(VectorScalar const& offset) noexcept;
    Transform& rotate(Scalar const angle) noexcept;
    Transform& rotate(Scalar const angle,
                      Scalar const centerX,
                      Scalar const centerY) noexcept;
    Transform& rotate(Scalar const angle, VectorScalar const& center) noexcept;
    Transform& scale(Scalar const scaleX, Scalar const scaleY) noexcept;
    Transform& scale(Scalar const scaleX,
                     Scalar const scaleY,
                     Scalar const centerX,
                     Scalar const centerY) noexcept;
    Transform& scale(VectorScalar const& factors) noexcept;
    Transform& scale(VectorScalar const& factors,
                     VectorScalar const& center) noexcept;

private:
    Scalar matrix_data_[16U];
};
}  // namespace haf::scene

#endif
