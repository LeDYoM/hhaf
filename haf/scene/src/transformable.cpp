#include "transformable.hpp"
#include "geometry_math.hpp"
#include <hlog/include/hlog.hpp>
#include <cmath>

using namespace mtps;

namespace haf::scene
{
Transformable::Transformable() noexcept :
    Transformation(),
    local_transform_{},
    global_transform_{},
    extra_transformations_{}
{}

Transformable::~Transformable() = default;

size_type Transformable::addTransformation()
{
    extra_transformations_.resize(extra_transformations_.size() + 1U);
    return numTransformations();
}

size_type Transformable::numTransformations() const noexcept
{
    return extra_transformations_.size() + 1U;
}

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

Transformation& Transformable::getTransformation(size_type const index) noexcept
{
    LogAsserter::log_assert(index < numTransformations());

    return (index == 0U || index >= numTransformations())
        ? static_cast<Transformation&>(*this)
        : extra_transformations_[index - 1U];
}

void Transformable::updateGlobalTransformation(
    Matrix4x4 const& currentGlobalTransformation) noexcept
{
    global_transform_ = currentGlobalTransformation * Transformation::matrix();
}

}  // namespace haf::scene
