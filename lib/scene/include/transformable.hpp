#pragma once

#ifndef LIB_TRANSFORMABLE_INCLUDE_HPP
#define LIB_TRANSFORMABLE_INCLUDE_HPP

#include "transform.hpp"
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/properties.hpp>

namespace lib::scene
{
class Transformable
{
public:
    using Scalar = Transform::Scalar;
    using VectorScalar = Transform::VectorScalar;

    Transformable() noexcept;
    virtual ~Transformable();

    PropertyState<VectorScalar> origin;
    PropertyState<Scalar> rotation;
    PropertyState<VectorScalar> scale;
    PropertyState<VectorScalar> position;

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

    void rotateScaleAround(vector2df point, f32 angle, vector2df scale);

protected:
    bool transformationNeedsUpdate() const noexcept;
    void updateGlobalTransformation(const Transform &) noexcept;

private:
    void resetNeedsUpdate() noexcept;
    void updateTransform() noexcept;

    Transform m_transform;
    Transform m_globalTransform;
};
} // namespace lib::scene

#endif
