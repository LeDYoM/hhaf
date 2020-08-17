#include "transformable.hpp"
#include "geometry_math.hpp"
#include <cmath>

namespace haf::scene
{
Transformable::Transformable() noexcept :
    Transformation(),
    local_transform_{},
    global_transform_{}
{}

Transformable::~Transformable() = default;

bool Transformable::updateLocalTransformationsIfNecessary() noexcept
{
    bool const result = updateTransformIfNecessary();

    if (result)
    {
        // If any of the transformations has changed, update our local
        // transformation.
        local_transform_ = Transformation::matrix();
    }
    return result;
}

void Transformable::updateGlobalTransformation(
    Matrix4x4 const& currentGlobalTransformation) noexcept
{
    global_transform_ = currentGlobalTransformation * Transformation::matrix();
}

void Transformable::updateTransform()
{
    Transformation::updateTransform();
}

}  // namespace haf::scene
