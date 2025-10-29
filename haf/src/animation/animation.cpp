#include <haf/include/animation/animation.hpp>
#include <hlog/include/hlog.hpp>

using namespace haf::core;
using namespace haf::time;

namespace haf::anim
{
Animation::Animation(AnimationProperties&& animation_data) noexcept :
    m_animation_data{htps::move(animation_data)},
    m_current_direction{m_animation_data.AnimationDirectionProperty()},
    m_current_time{TimePoint{}},
    m_raw_delta{static_cast<AnimationDeltaType>(0.0)},
    m_delta{postProcessDelta(m_raw_delta)},
    m_end_reached{false}
{}

Animation::~Animation() = default;

bool Animation::animate()
{
    executeStartAction();
    m_current_time = m_animation_data.TimerProperty()->ellapsed();

    bool continue_animation{m_current_time <= m_animation_data.Duration()};
    m_raw_delta = (continue_animation)
        ? (static_cast<decltype(m_raw_delta)>(m_current_time.milliseconds()) /
           m_animation_data.Duration().milliseconds())
        : static_cast<AnimationDeltaType>(1.0);

    m_delta       = postProcessDelta(m_raw_delta);
    m_end_reached = !continue_animation;

    if (m_end_reached)
    {
        // Should we stop animations?
        // Reduce the number of pending loops if animation type is not
        // infinite
        if (m_animation_data.Times() != -1)
        {
            m_animation_data.Times = m_animation_data.Times() - 1;
        }
        continue_animation = m_animation_data.Times() != 0;

        if (continue_animation)
        {
            if (m_animation_data.Switch())
            {
                m_current_direction =
                    ((m_current_direction == AnimationDirection::Forward)
                         ? AnimationDirection::Backward
                         : AnimationDirection::Forward);
            }
            m_animation_data.TimerProperty()->restart();
        }
    }
    return continue_animation;
}

void Animation::executeStartAction()
{
    if (m_current_time == TimePoint{} &&
        m_animation_data.ActionBeforeStarting())
    {
        m_animation_data.ActionBeforeStarting()();
    }
}

void Animation::executeEndAction()
{
    m_animation_data.TimerProperty()->markToDelete();
    // If property containing the function wrapper contains a function, call it
    if (m_animation_data.ActionWhenFinished())
    {
        m_animation_data.ActionWhenFinished()();
    }
}

f32 Animation::postProcessDelta(AnimationDeltaType const delta)
{
    switch (m_current_direction)
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
