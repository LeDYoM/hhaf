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
    using timer_emitter_t = emitter<time::TimePoint>;
    using timer_callback_t = timer_emitter_t::emitter_callback_t;

    class ITimer
    {
    private:
        ITimer(time::TimePoint timePoint, time::TimePoint currentTime, timer_callback_t callback)
            : m_delta{ timePoint }, m_lastCheck{ currentTime }, m_callback { std::move(callback) } {}
        time::TimePoint m_delta;
        time::TimePoint m_lastCheck;
        timer_callback_t m_callback;
    };

    class TimerComponent : public IComponent
	{
	public:
        sptr<ITimer> addTimer(time::TimePoint deltaTime, timer_callback_t callback) {
            auto timer(msptr<ITimer>(deltaTime, std::move(callback)));
            m_activeTimers.push_back(timer);
            return timer;
        }
	private:
        vector_weak_pointers<ITimer> m_activeTimers;
        vector_weak_pointers<ITimer> m_oneShotTimers;
	};
}

#endif
