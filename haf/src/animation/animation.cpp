#include <haf/include/animation/animation.hpp>
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::anim
{
Animation::Animation(AnimationProperties&& animation_data) noexcept :
    animation_data_{htps::move(animation_data)},
    current_direction_{animation_data_.prop<AnimationDirectionProperty>()()},
    current_time_{},
    raw_delta_{static_cast<AnimationDeltaType>(0.0)},
    delta_{postProcessDelta(raw_delta_)},
    end_reached_{false}
{}

Animation::~Animation() = default;

bool Animation::animate()
{
    current_time_ = animation_data_.prop<TimerProperty>()()->ellapsed();

    bool continue_animation{current_time_ <=
                            animation_data_.prop<Duration>()()};
    raw_delta_ = (continue_animation)
        ? (static_cast<decltype(raw_delta_)>(current_time_.milliseconds()) /
           animation_data_.prop<Duration>()().milliseconds())
        : static_cast<AnimationDeltaType>(1.0);

    delta_       = postProcessDelta(raw_delta_);
    end_reached_ = !continue_animation;

    if (end_reached_)
    {
        // Should we stop animations?
        // Reduce the number of pending loops if animation type is not
        // infinite
        if (animation_data_.prop<Times>()() != -1)
        {
            animation_data_.prop<Times>() = animation_data_.prop<Times>()() - 1;
        }
        continue_animation = animation_data_.prop<Times>()() != 0;

        if (continue_animation)
        {
            if (animation_data_.prop<Switch>()())
            {
                current_direction_ =
                    ((current_direction_ == AnimationDirection::Forward)
                         ? AnimationDirection::Backward
                         : AnimationDirection::Forward);
            }
            animation_data_.prop<TimerProperty>()()->restart();
        }
    }
    return continue_animation;
}

void Animation::executeEndAction()
{
    animation_data_.prop<TimerProperty>()()->markToDelete();
    // If property containing the function wrapper contains a function, call it
    if (animation_data_.prop<ActionWhenFinished>()())
    {
        animation_data_.prop<ActionWhenFinished>()()();
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
