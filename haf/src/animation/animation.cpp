#include <haf/include/animation/animation.hpp>

using namespace htps;

namespace haf::anim
{
Animation::Animation(uptr<time::Timer> timer,
                     time::TimePoint duration,
                     const AnimationDirection animation_direction,
                     ActionFunc endAction) noexcept :
    animation_data_{std::move(timer), std::move(duration),
    std::move(endAction), std::move(animation_direction)},
    m_currentTime{},
    raw_delta_{0.0F},
    delta_{postProcessDelta(raw_delta_)}
{}

Animation::~Animation() = default;

bool Animation::animate()
{
    m_currentTime = animation_data_.timer_->ellapsed();
    if (m_currentTime > animation_data_.m_duration)
    {
        delta_ = postProcessDelta(1.0F);
        return false;
    }
    raw_delta_ = static_cast<f32>(m_currentTime.milliseconds()) /
        animation_data_.m_duration.milliseconds();
    delta_ = postProcessDelta(raw_delta_);
    return true;
}

void Animation::executeEndAction()
{
    if (animation_data_.m_endAction)
    {
        animation_data_.m_endAction();
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
