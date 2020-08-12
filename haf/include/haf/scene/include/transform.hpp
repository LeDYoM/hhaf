#pragma once

#ifndef HAF_TRANSFORMN_INCLUDE_HPP
#define HAF_TRANSFORM_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace haf::scene
{
class Transform final
{
public:
    using Scalar = mtps::f32;

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

    constexpr Transform(Transform const&) noexcept = default;
    Transform& operator=(Transform const&) noexcept = default;

    constexpr Transform(Transform&&) noexcept = default;
    Transform& operator=(Transform&&) noexcept = default;

    constexpr mtps::rptr<Scalar const> const getMatrix() const noexcept
    {
        return matrix_data_.cbegin();
    }

    static Transform const Identity;

    Transform& operator*=(Transform const& right) noexcept;
    Transform operator*(Transform const& right) const noexcept;

private:
    std::array<Scalar, 16U> matrix_data_;
};
}  // namespace haf::scene

#endif
