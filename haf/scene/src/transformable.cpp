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

void Transformable::updateTransform()
{
    Transformation::updateTransform();
}

}  // namespace haf::scene
