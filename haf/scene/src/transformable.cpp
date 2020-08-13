#include "transformable.hpp"
#include "geometry_math.hpp"
#include <cmath>

namespace haf::scene
{
Transformable::Transformable() noexcept :
    origin{},
    rotation{},
    scale{{1U, 1U}},
    position{},
    transform_{},
    global_transform_{}
{}

Transformable::~Transformable() = default;

bool Transformable::updateTransformIfNecessary() noexcept
{
    if (ps_hasChanged(position, origin, scale, rotation))
    {
        updateTransform();
        ps_resetHasChanged(origin, rotation, scale, position);
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
    origin   = point;
    rotation = angle;
}

void Transformable::scaleAround(VectorScalar const point,
                                VectorScalar const scale_) noexcept
{
    origin = point;
    scale  = scale_;
}

void Transformable::updateTransform()
{
    // Recompute the combined transform
    auto const angle{-rotation() * ToRadians<Scalar>};
    VectorScalar const sc{scale() * static_cast<Scalar>(std::cos(angle))};
    VectorScalar const ss{scale() * static_cast<Scalar>(std::sin(angle))};
    VectorScalar const orig{origin()};
    VectorScalar const pos{position()};

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
