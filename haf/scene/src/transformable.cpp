#include <haf/scene/include/transformable.hpp>
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
    bool result{false};

    for (auto index{0}; index < numTransformations(); ++index)
    {
        result |= getTransformation(index).updateTransformIfNecessary();
    }

    // Result contains if any of the sub local transformations has changed.
    if (result)
    {
        local_transform_ = Matrix4x4::Identity;
        for (auto index{0}; index < numTransformations(); ++index)
        {
            local_transform_ *= getTransformation(index).matrix();
        }
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
    global_transform_ = currentGlobalTransformation * local_transform_;
}

}  // namespace haf::scene
