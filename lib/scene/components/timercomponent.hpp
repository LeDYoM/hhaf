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
    public:
        ITimer(time::TimePoint timePoint, timer_callback_t callback)
            : delta{ timePoint }, lastCheck{ time::Clock().now() }, callback { std::move(callback) } {}
	private:
        time::TimePoint delta;
        time::TimePoint lastCheck;
        timer_callback_t callback;
        friend class TimerComponent;
    };

    class TimerComponent : public IComponent
	{
	public:
        sptr<ITimer> addTimer(time::TimePoint deltaTime, timer_callback_t callback) {
            auto timer(msptr<ITimer>(deltaTime, std::move(callback)));
            m_activeTimers.push_back(timer);
            return timer;
        }

        void update() override;

	private:
        vector_weak_pointers<ITimer> m_activeTimers;
        vector_weak_pointers<ITimer> m_oneShotTimers;
	};
}

#endif
