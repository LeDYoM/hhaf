#pragma once

#ifndef HAF_SCENE_TRANSFORMABLE_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMABLE_INCLUDE_HPP

#include "matrix4x4.hpp"
#include "transformation_properties.hpp"
#include "transformation.hpp"
#include <mtypes/include/vector.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/propertystate.hpp>

namespace haf::scene
{
class Transformable : public Transformation
{
public:
    using BaseClass = Transformation;
    using BaseClass::prop;

    using Scalar       = Matrix4x4::Scalar;
    using VectorScalar = mtps::vector2d<Scalar>;
    using RectScalar   = mtps::Rect<Scalar>;

    Transformable() noexcept;
    virtual ~Transformable();

    inline Matrix4x4 const& globalTransform() const noexcept
    {
        return global_transform_;
    }

    using Transformation::rotateAround;
    using Transformation::scaleAround;

    mtps::size_type addTransformation();
    mtps::size_type numTransformations() const noexcept;

    bool updateLocalTransformationsIfNecessary() noexcept;
    void updateGlobalTransformation(Matrix4x4 const&) noexcept;

    Transformation& getTransformation(mtps::size_type const index) noexcept;

private:
    Matrix4x4 global_transform_;
    Matrix4x4 local_transform_;

    mtps::vector<Transformation> extra_transformations_;
};
}  // namespace haf::scene

#endif
