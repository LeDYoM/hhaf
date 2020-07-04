#pragma once

#ifndef HAF_TRANSFORMABLE_INCLUDE_HPP
#define HAF_TRANSFORMABLE_INCLUDE_HPP

#include "transform.hpp"
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/properties.hpp>

namespace haf::scene
{
class Transformable
{
public:
    using Scalar       = Transform::Scalar;
    using VectorScalar = mtps::vector2d<Scalar>;
    using RectScalar   = mtps::Rect<Scalar>;

    Transformable() noexcept;
    virtual ~Transformable();

    mtps::PropertyState<VectorScalar> origin;
    mtps::PropertyState<Scalar> rotation;
    mtps::PropertyState<VectorScalar> scale;
    mtps::PropertyState<VectorScalar> position;

    bool updateTransformIfNecessary() noexcept;
    inline Transform const& globalTransform() const noexcept
    {
        return global_transform_;
    }

    /**
     * @brief Set the associated transformation to a rotation around a given
     * point.
     *
     * @param point Point to be rotated around
     * @param angle Angle for the rotation
     */
    void rotateAround(VectorScalar const point, Scalar const angle) noexcept;

    /**
     * @brief Set the associated transformation to a scale around a given point.
     * Note: this method overwrites the properties.
     *
     * @param point Point to be rotated around
     * @param scale Scale factor
     */
    void scaleAround(VectorScalar const point,
                     VectorScalar const scale) noexcept;

    void updateGlobalTransformation(Transform const&) noexcept;

private:
    void updateTransform();

    Transform transform_;
    Transform global_transform_;
};
}  // namespace haf::scene

#endif
