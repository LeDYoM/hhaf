#ifndef HAF_ANIMATION_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/animation_data.hpp>

namespace haf::anim
{
class AnimationBuilder
{
    AnimationBuilder& duration(time::TimePoint _duration);
    AnimationBuilder& endAction(ActionFunc _end_action);
    AnimationBuilder& animationDirection(
        AnimationDirection _animation_direction);

    AnimationData animationData() noexcept;
private:
    AnimationData data_;
};
}  // namespace haf::anim

#endif
