#ifndef HAF_SCENE_TRANSFORMATION_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMATION_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include "matrix4x4.hpp"
#include "transformation_properties.hpp"
#include <htypes/include/vector2d.hpp>
#include <htypes/include/rect.hpp>
#include <htypes/include/propertystate.hpp>

namespace haf::scene
{
class HAF_API Transformation : public TransformationProperties
{
public:
    using BaseClass = TransformationProperties;
    using BaseClass::prop;

    using Scalar       = Matrix4x4::Scalar;
    using VectorScalar = htps::vector2d<Scalar>;
    using RectScalar   = htps::Rect<Scalar>;

    Transformation() noexcept;
    virtual ~Transformation();
    Transformation(Transformation const&) = delete;
    Transformation& operator=(Transformation const&) = delete;
    Transformation(Transformation&&) noexcept        = default;
    Transformation& operator=(Transformation&&) noexcept = default;

    bool updateTransformIfNecessary() noexcept;

    Matrix4x4 const& matrix() noexcept { return transform_; }

private:
    void updateTransform();

    Matrix4x4 transform_;
};
}  // namespace haf::scene

#endif
