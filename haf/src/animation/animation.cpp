#include <haf/include/animation/animation.hpp>

using namespace htps;

namespace haf::anim
{
Animation::Animation(uptr<time::Timer> timer,
                     time::TimePoint duration,
                     const AnimationDirection animation_direction,
                     ActionFunc endAction) noexcept :
    animation_data_{std::move(timer), std::move(duration), std::move(endAction),
                    std::move(animation_direction)},
    current_time_{},
    raw_delta_{0.0F},
    delta_{postProcessDelta(raw_delta_)}
{}

Animation::~Animation() = default;

bool Animation::animate()
{
    current_time_ = animation_data_.timer_->ellapsed();
    if (current_time_ > animation_data_.duration_)
    {
        delta_ = postProcessDelta(1.0F);
        return false;
    }
    raw_delta_ =
        static_cast<decltype(raw_delta_)>(current_time_.milliseconds()) /
        animation_data_.duration_.milliseconds();
    delta_ = postProcessDelta(raw_delta_);
    return true;
}

void Animation::executeEndAction()
{
    if (animation_data_.end_action_)
    {
        animation_data_.end_action_();
    }
}

f32 Animation::postProcessDelta(const f32 delta)
{
    switch (animation_data_.animation_direction_)
    {
        default:
        case AnimationDirection::Forward:
            return delta;
            break;
        case AnimationDirection::Backward:
            return (1.0F - delta);
            break;
    }
}
}  // namespace haf::anim
