#include "transformable.hpp"
#include "geometry_math.hpp"
#include <cmath>

namespace haf::scene
{
Transformable::Transformable() noexcept :
    Transformation(),
    transform_{},
    global_transform_{}
{}

Transformable::~Transformable() = default;

bool Transformable::updateTransformIfNecessary() noexcept
{
    if (anyHasChanged(prop<TransformationProperties>()))
    {
        updateTransform();
        resetHasChanged(prop<TransformationProperties>());
        return true;
    }
    return false;
}

void Transformable::updateGlobalTransformation(
    Matrix4x4 const& currentGlobalTransformation) noexcept
{
    global_transform_ = currentGlobalTransformation * transform_;
}

void Transformable::rotateAround(VectorScalar const point,
                                 Scalar const angle) noexcept
{
    prop<Origin>()   = point;
    prop<Rotation>() = angle;
}

void Transformable::scaleAround(VectorScalar const point,
                                VectorScalar const scale_) noexcept
{
    prop<Origin>() = point;
    prop<Scale>()  = scale_;
}

void Transformable::updateTransform()
{
    // Recompute the combined transform
    auto const angle{-prop<Rotation>().get() * ToRadians<Scalar>};
    VectorScalar const sc{prop<Scale>().get() *
                          static_cast<Scalar>(std::cos(angle))};
    VectorScalar const ss{prop<Scale>().get() *
                          static_cast<Scalar>(std::sin(angle))};
    VectorScalar const orig{prop<Origin>().get()};
    VectorScalar const pos{prop<Position>().get()};

    transform_ = {sc.x,
                  ss.y,
                  (((-orig.x * sc.x) - (orig.y * ss.y)) + pos.x),
                  -ss.x,
                  sc.y,
                  (((orig.x * ss.y) - (orig.y * sc.y)) + pos.y),
                  Matrix4x4::Zero,
                  Matrix4x4::Zero,
                  Matrix4x4::One};
}
}  // namespace haf::scene
