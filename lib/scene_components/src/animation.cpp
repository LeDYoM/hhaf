#include "animation.hpp"

namespace lib::scene
{

IAnimation::IAnimation(uptr<time::Timer> timer, time::TimePoint duration,
                       const AnimationDirection animation_direction,
                       ActionFunc endAction) noexcept
    : timer_{std::move(timer)}, m_duration{std::move(duration)},
      animation_direction_{std::move(animation_direction)},
      m_endAction{std::move(endAction)}, raw_delta_{0.0F},
      delta_{postProcessDelta(raw_delta_)} {}

IAnimation::~IAnimation() = default;

bool IAnimation::animate()
{
    m_currentTime = timer_->ellapsed();
    if (m_currentTime > m_duration)
    {
        delta_ = postProcessDelta(1.0F);
        return false;
    }
    raw_delta_ = static_cast<f32>(
                     m_currentTime.milliseconds()) /
                 m_duration.milliseconds();
    delta_ = postProcessDelta(raw_delta_);
    return true;
}

void IAnimation::executeEndAction()
{
    if (m_endAction)
    {
        m_endAction();
    }
}

f32 IAnimation::postProcessDelta(const f32 delta)
{
    switch (animation_direction_)
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
} // namespace lib::scene
