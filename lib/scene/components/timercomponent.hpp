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
    using timer_emitter_t = emitter<Time>;
    using timer_callback_t = timer_emitter_t::emitter_callback_t;

    class TimerConnector
    {
    public:
        TimerConnector(Time timeOut, timer_callback_t emitter)
            : m_timer{ }, m_timeOut{ std::move(timeOut) },
            m_emitter { std::move(emitter) } {}

        inline bool timeOut() const { return m_timer.getElapsedTime() >= m_timeOut; }
    private:
        Timer m_timer;
        Time m_timeOut;
        timer_emitter_t m_emitter;
        friend class TimerComponent;
    };

    using TimerConnectorSPtr = sptr<TimerConnector>;

    class TimerComponent : public IComponent
	{
	public:
        TimerConnectorSPtr addTimer(Time timeOut, timer_callback_t callback) {
            auto timerConnector(msptr<TimerConnector>(std::move(timeOut), std::move(callback)));
            m_activeTimers.push_back(timerConnector);
            return timerConnector;
        }

        void update() override;

	private:
        vector_shared_pointers<TimerConnector> m_activeTimers;
        vector_shared_pointers<TimerConnector> m_oneShotTimers;
	};
}

#endif
