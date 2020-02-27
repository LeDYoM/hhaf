#pragma once

#ifndef LIB_SCENE_IANIMATION_INCLUDE_HPP
#define LIB_SCENE_IANIMATION_INCLUDE_HPP

#include <lib/time/include/timepoint.hpp>
#include <lib/time/include/timeview.hpp>
#include <lib/time/include/timer.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>

namespace lib::scene
{
class IAnimation
{
public:
    using ActionFunc = function<void()>;
    enum class AnimationDirection : u8
    {
        Forward = 0U,
        Backward
    };

    IAnimation(uptr<time::Timer> timer, time::TimePoint duration,
               const AnimationDirection animation_direction, 
               ActionFunc endAction = {}) noexcept
        : timer_{std::move(timer)}, m_duration{std::move(duration)},
          animation_direction_{std::move(animation_direction)},
          m_endAction{std::move(endAction)}, raw_delta_{0.0F},
          delta_{postProcessDelta(raw_delta_)} {}

    virtual bool animate()
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

    constexpr void executeEndAction()
    {
        if (m_endAction)
        {
            m_endAction();
        }
    }

    virtual ~IAnimation() {}

protected:
    uptr<time::Timer> timer_;
    time::TimePoint m_duration;
    time::TimePoint m_currentTime;
    ActionFunc m_endAction;
    AnimationDirection animation_direction_;
    f32 raw_delta_;
    f32 delta_;

private:
    f32 postProcessDelta(const f32 delta)
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
};

} // namespace lib::scene

#endif
