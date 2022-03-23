#include <haf/include/scene/transformation.hpp>
#include "render/geometry_math.hpp"

#include <cmath>

namespace haf::scene
{
Transformation::Transformation() noexcept :
    TransformationProperties({}, {1U, 1U}, {}), transform_{}
{}

Transformation::~Transformation() = default;

bool Transformation::updateTransformIfNecessary() noexcept
{
    if (anyHasChanged(prop<TransformationProperties>()))
    {
        updateTransform();
        resetHasChanged(prop<TransformationProperties>());
        return true;
    }
    return false;
}

void Transformation::updateTransform()
{
    // Recompute the combined transform
    auto const angle{-prop<Rotation>()() * render::ToRadians<Scalar>};
    VectorScalar const scale_cos{prop<Scale>()() *
                                 static_cast<Scalar>(std::cos(angle))};
    VectorScalar const scale_sin{prop<Scale>()() *
                                 static_cast<Scalar>(std::sin(angle))};
    VectorScalar const position{prop<Position>()()};

    transform_ = {scale_cos.x,     scale_sin.y,     position.x,
                  -scale_sin.x,    scale_cos.y,     position.y,
                  Matrix4x4::Zero, Matrix4x4::Zero, Matrix4x4::One};
}

Matrix4x4 const& Transformation::matrix() noexcept
{
    return transform_;
}

void Transformation::setLeftTopPositionScale(VectorScalar const& vector)
{
    prop<Position>().set(VectorScalar{-0.5F, -0.5F} + (vector / 2.0F));
    prop<Scale>().set(vector);
}

}  // namespace haf::scene
