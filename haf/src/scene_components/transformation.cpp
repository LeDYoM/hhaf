#include <haf/include/scene_components/transformation.hpp>
#include "render/geometry_math.hpp"

#include <cmath>

namespace haf::scene
{
Transformation::Transformation() noexcept : transform_{}
{}

Transformation::~Transformation() = default;

bool Transformation::updateTransformIfNecessary() noexcept
{
    if (ps_readResetHasAnyChanged(Position, Scale, Rotation))
    {
        updateTransform();
        return true;
    }
    return false;
}

void Transformation::updateTransform()
{
    // Recompute the combined transform
    auto const angle{-Rotation() * render::ToRadians<Scalar>};
    VectorScalar const scale_cos{Scale() *
                                 static_cast<Scalar>(std::cos(angle))};
    VectorScalar const scale_sin{Scale() *
                                 static_cast<Scalar>(std::sin(angle))};
    VectorScalar const position{Position()};

    transform_ = {scale_cos.x,     scale_sin.y,     position.x,
                  -scale_sin.x,    scale_cos.y,     position.y,
                  Matrix4x4::Zero, Matrix4x4::Zero, Matrix4x4::One};
}

Matrix4x4 const& Transformation::matrix() const noexcept
{
    return transform_;
}

void Transformation::setLeftTopPositionScale(VectorScalar const& vector)
{
    Position = VectorScalar{-0.5F, -0.5F} + (vector / 2.0F);
    Scale    = vector;
}

void Transformation::setRightTopPositionScale(VectorScalar const& vector)
{
    VectorScalar origin{0.5F, -0.5F};
    origin.x -= vector.x / 2.0F;
    origin.y += vector.y / 2.0F;
    Position = htps::move(origin);
    Scale    = vector;
}

}  // namespace haf::scene
