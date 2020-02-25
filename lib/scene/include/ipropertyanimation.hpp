#pragma once

#ifndef LIB_SCENE_IPROPERTY_ANIMATION_INCLUDE_HPP
#define LIB_SCENE_IANIMATION_INCLUDE_HPP

#include <lib/time/include/timepoint.hpp>
#include <lib/time/include/timeview.hpp>
#include <lib/time/include/timer.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/include/ianimation.hpp>

namespace lib::scene
{

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
