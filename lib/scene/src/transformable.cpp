#include "transformable.hpp"
#include "geometry_math.hpp"
#include <cmath>

using namespace mtps;

namespace lib::scene
{
Transformable::Transformable() noexcept :
    origin{},
    rotation{},
    scale{{1U, 1U}},
    position{},
    m_transform{},
    m_globalTransform{}
{}

Transformable::~Transformable() = default;

bool Transformable::updateTransformIfNecessary() noexcept
{
    if (transformationNeedsUpdate())
    {
        updateTransform();
        resetNeedsUpdate();
        return true;
    }
    return false;
}

void Transformable::resetNeedsUpdate() noexcept
{
    ps_resetHasChanged(origin, rotation, scale, position);
}

bool Transformable::transformationNeedsUpdate() const noexcept
{
    return ps_hasChanged(position, origin, scale, rotation);
}

void Transformable::updateGlobalTransformation(
    const Transform& currentGlobalTransformation) noexcept
{
    m_globalTransform = currentGlobalTransformation * m_transform;
}

void Transformable::rotateAround(VectorScalar point, Scalar angle)
{
    origin = position = point;
    rotation          = angle;
}

void Transformable::scaleAround(VectorScalar point, VectorScalar scale_)
{
    origin = position = point;
    scale             = scale_;
}

void Transformable::rotateScaleAround(VectorScalar point,
                                      f32 angle,
                                      VectorScalar scale_)
{
    origin = position = point;
    rotation          = angle;
    scale             = scale_;
}

void Transformable::updateTransform() noexcept
{
    // Recompute the combined transform
    const Scalar angle{-rotation() * ToRadians<Scalar>},
        cosine{static_cast<Scalar>(std::cos(angle))},
        sine{static_cast<Scalar>(std::sin(angle))};
    const VectorScalar sc{scale() * cosine}, ss{scale() * sine}, orig{origin()},
        pos{position()};

    m_transform = {sc.x,
                   ss.y,
                   (((-orig.x * sc.x) - (orig.y * ss.y)) + pos.x),
                   -ss.x,
                   sc.y,
                   (((orig.x * ss.y) - (orig.y * sc.y)) + pos.y),
                   Transform::Zero,
                   Transform::Zero,
                   Transform::One};
}
}  // namespace lib::scene
