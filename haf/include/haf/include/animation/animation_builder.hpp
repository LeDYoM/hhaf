#ifndef HAF_ANIMATION_ANIMATION_BUILDER_INCLUDE_HPP
#define HAF_ANIMATION_ANIMATION_BUILDER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/animation_data.hpp>
#include <haf/include/time/timer.hpp>

namespace haf::anim
{
class AnimationBuilder
{
public:
    AnimationBuilder& duration(time::TimePoint _duration);
    AnimationBuilder& endAction(ActionFunc _end_action);
    AnimationBuilder& animationDirection(
        AnimationDirection _animation_direction);
    AnimationBuilder& timer(htps::uptr<time::Timer> timer);

    AnimationData extractData() noexcept;

private:
    AnimationData data_;
};

}  // namespace haf::anim

#endif
