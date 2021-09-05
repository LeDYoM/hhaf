#include <haf/include/animation/animation.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::anim
{
Animation::Animation(AnimationData&& animation_data) noexcept :
    animation_data_{std::move(animation_data)},
    current_direction_{animation_data_.animation_direction_},
    current_time_{},
    raw_delta_{0.0F},
    delta_{postProcessDelta(raw_delta_)},
    end_reached_{false}
{}

Animation::~Animation() = default;

bool Animation::animate()
{
    current_time_ = animation_data_.timer_->ellapsed();

    bool const continue_animation{current_time_ <= animation_data_.duration_};
    raw_delta_ = (continue_animation) ? (
        static_cast<decltype(raw_delta_)>(current_time_.milliseconds()) /
        animation_data_.duration_.milliseconds()) : 1.0F;

    delta_ = postProcessDelta(raw_delta_);
    return continue_animation;
}

void Animation::executeEndAction()
{
    if (animation_data_.end_action_)
    {
        animation_data_.end_action_();
    }
}

f32 Animation::postProcessDelta(AnimationDeltaType const delta)
{
    switch (current_direction_)
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
