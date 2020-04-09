#pragma once

#ifndef HAF_TRANSFORMABLE_INCLUDE_HPP
#define HAF_TRANSFORMABLE_INCLUDE_HPP

#include "transform.hpp"
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/properties.hpp>

namespace haf::scene
{
class Transformable
{
public:
    using Scalar = Transform::Scalar;
    using VectorScalar = Transform::VectorScalar;

    Transformable() noexcept;
    virtual ~Transformable();

    mtps::PropertyState<VectorScalar> origin;
    mtps::PropertyState<Scalar> rotation;
    mtps::PropertyState<VectorScalar> scale;
    mtps::PropertyState<VectorScalar> position;

    bool updateTransformIfNecessary() noexcept;
    inline const Transform &globalTransform() const noexcept { return m_globalTransform; }

    /// Method to set the associated transformation to a rotation around a given point.
    /// Note: this method overwrites the properties.
    /// @param [in] point Point to be rotated around
    /// @param [in] angle Angle for the rotation
    void rotateAround(VectorScalar point, Scalar angle);

    /// Method to set the associated transformation to a scale around a given point.
    /// Note: this method overwrites the properties.
    /// @param [in] point Point to be rotated around
    /// @param [in] scale Scale factor
    void scaleAround(VectorScalar point, VectorScalar scale);

    void rotateScaleAround(mtps::vector2df point, mtps::f32 angle, mtps::vector2df scale);

protected:
    bool transformationNeedsUpdate() const noexcept;
    void updateGlobalTransformation(const Transform &) noexcept;

private:
    void resetNeedsUpdate() noexcept;
    void updateTransform() noexcept;

    Transform m_transform;
    Transform m_globalTransform;
};
} // namespace haf::scene

#endif
