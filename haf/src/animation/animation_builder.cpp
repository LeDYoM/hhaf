#include <haf/include/animation/animation_builder.hpp>
#include <haf/include/animation/animationcomponent.hpp>

using namespace htps;

namespace haf::anim
{
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

AnimationBuilder& AnimationBuilder::timer(htps::uptr<time::Timer> timer)
{
    data_.timer_ = std::move(timer);
    return *this;
}

AnimationData AnimationBuilder::extractData() noexcept
{
    return std::move(data_);
}

}  // namespace haf::anim
