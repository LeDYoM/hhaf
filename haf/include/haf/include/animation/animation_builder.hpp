#ifndef HAF_ANIMATION_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/animation_data.hpp>

namespace haf::anim
{
class AnimationComponent;

class AnimationBuilder
{
    AnimationBuilder(htps::rptr<AnimationComponent>) noexcept;

    AnimationBuilder& duration(time::TimePoint _duration);
    AnimationBuilder& endAction(ActionFunc _end_action);
    AnimationBuilder& animationDirection(
        AnimationDirection _animation_direction);

private:
    htps::rptr<AnimationComponent> animation_component_;
    AnimationData data_;
};
}  // namespace haf::anim

#endif
