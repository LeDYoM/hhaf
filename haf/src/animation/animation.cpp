#include <haf/include/animation/animation.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::anim
{
Animation::Animation(AnimationData&& animation_data) noexcept :
    animation_data_{std::move(animation_data)},
    current_direction_{animation_data_.animation_direction_},
    current_time_{},
    raw_delta_{static_cast<AnimationDeltaType>(0.0)},
    delta_{postProcessDelta(raw_delta_)},
    end_reached_{false}
{}

Animation::~Animation() = default;

bool Animation::animate()
{
    current_time_ = animation_data_.timer_->ellapsed();

    bool continue_animation{current_time_ <= animation_data_.duration_};
    raw_delta_ = (continue_animation)
        ? (static_cast<decltype(raw_delta_)>(current_time_.milliseconds()) /
           animation_data_.duration_.milliseconds())
        : static_cast<AnimationDeltaType>(1.0);

    delta_       = postProcessDelta(raw_delta_);
    end_reached_ = !continue_animation;

    if (end_reached_)
    {
        // Should we stop animations?
        // Reduce the number of pending loops if animation type is not
        // infinite
        if (animation_data_.times_ != -1)
        {
            --animation_data_.times_;
        }
        continue_animation = animation_data_.times_ != 0;

        if (continue_animation)
        {
            if (animation_data_.switch_)
            {
                current_direction_ =
                    ((current_direction_ == AnimationDirection::Forward)
                         ? AnimationDirection::Backward
                         : AnimationDirection::Forward);
            }
            animation_data_.timer_->restart();
        }
    }
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
            return (static_cast<AnimationDeltaType>(1.0) - delta);
            break;
    }
}
}  // namespace haf::anim
