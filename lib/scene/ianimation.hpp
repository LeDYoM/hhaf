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
using ActionFunc = function<void()>;
class IAnimation
{
public:
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

template <typename T>
class IPropertyAnimation : public IAnimation
{
public:
    IPropertyAnimation(uptr<time::Timer> timer, time::TimePoint duration, IProperty<T> &prop,
                       T start, T end, ActionFunc endAction = {})
        : IAnimation{std::move(timer), std::move(duration), std::move(endAction)},
          m_property{prop}, m_startValue{std::move(start)},
          m_endValue{std::move(end)}, m_deltaValue{m_endValue - m_startValue} {}

    virtual bool animate() override
    {
        const bool bResult{IAnimation::animate()};
        m_property.set(T{m_startValue + (m_deltaValue * m_delta)});
        return bResult;
    }

protected:
    IProperty<T> &m_property;
    T m_startValue;
    T m_endValue;
    T m_deltaValue;
};
} // namespace lib::scene

#endif
