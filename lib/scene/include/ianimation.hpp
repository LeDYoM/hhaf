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

    IAnimation(uptr<time::Timer> timer, time::TimePoint duration, ActionFunc endAction = {}) noexcept
        : timer_{std::move(timer)}, m_duration{std::move(duration)}, m_endAction{std::move(endAction)} {}

    virtual bool animate()
    {
        m_currentTime = timer_->ellapsed();
        if (m_currentTime > m_duration)
        {
            m_delta = 1.0f;
            return false;
        }
        m_delta = (static_cast<decltype(m_delta)>(
                       m_currentTime.milliseconds()) /
                   m_duration.milliseconds());
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
    f32 m_delta{0.0f};
    ActionFunc m_endAction;
};

} // namespace lib::scene

#endif
