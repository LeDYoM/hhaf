#pragma once

#ifndef LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP__
#define LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <mtypes/include/timer.hpp>
#include <mtypes/include/vector.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib::scene
{
    using timer_callback_t = function<time::TimePoint>;

    class ITimer
    {
    private:
        constexpr ITimer(time::TimePoint timePoint, timer_callback_t callback)
            : m_deltaTime{ timePoint }, m_callback{ std::move(callback) } noexcept {}
        time::TimePoint m_deltaTime;
        timer_callback_t m_callback;
    };

    class TimerComponent : public IComponent
	{
	public:
        sptr<ITimer> addTimer(time::TimePoint deltaTime, timer_callback_t callback) {
            m_activeTimers.push_back(mwptr<ITimer>(deltaTime, std::move(callback)));
        }
	private:
        vector_of_weak_pointers<ITimer> m_activeTimers;
        vector<wptr<ITimer>> m_oneShotTimers;
	};
}

#endif
