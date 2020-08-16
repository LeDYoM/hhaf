#pragma once

#ifndef HAF_SCENE_TRANSFORMATION_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_INCLUDE_HPP

#include "matrix4x4.hpp"
#include "transformation_properties.hpp"
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/propertystate.hpp>

namespace haf::scene
{
class Transformation : public TransformationProperties
{
public:
    using BaseClass = TransformationProperties;
    using BaseClass::prop;

    using Scalar       = Matrix4x4::Scalar;
    using VectorScalar = mtps::vector2d<Scalar>;
    using RectScalar   = mtps::Rect<Scalar>;

    Transformation() noexcept;
    virtual ~Transformation();

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

    void updateGlobalTransformation(Matrix4x4 const&) noexcept;

private:
    void updateTransform();

    Matrix4x4 transform_;
};
}  // namespace haf::scene

#endif
