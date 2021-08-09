#include <haf/include/animation/animation_builder.hpp>

using namespace htps;

namespace haf::anim
{
AnimationBuilder::AnimationBuilder(
    htps::rptr<AnimationComponent> animation_component) noexcept :
    animation_component_{animation_component}
{}

AnimationBuilder& AnimationBuilder::duration(time::TimePoint _duration)
{
    data_.duration_ = std::move(_duration);
    return *this;
}

AnimationBuilder& AnimationBuilder::endAction(ActionFunc _end_action)
{
    data_.end_action_ = std::move(_end_action);
    return *this;
}

AnimationBuilder& AnimationBuilder::animationDirection(
    AnimationDirection _animation_direction)
{
    data_.animation_direction_ = std::move(_animation_direction);
    return *this;
}
}  // namespace haf::anim
