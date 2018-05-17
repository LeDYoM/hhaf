#pragma once

#ifndef LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP__
#define LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/include/core/timer.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/lockablevector.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/components/icomponent.hpp>

namespace lib::scene
{
    using timer_emitter_t = emitter<Time>;
    using timer_callback_t = timer_emitter_t::emitter_callback_t;

    enum class TimerType : u8
    {
        Continuous,
        OneShot
    };

    class TimerConnector
    {
    public:
        TimerConnector(TimerType timerType, Time timeOut, timer_callback_t emitter)
            : m_timer{ }, m_timeOut{ std::move(timeOut) },
            m_emitter{ std::move(emitter) }, m_timerType{ timerType } {}

        inline bool timeOut() const { return m_timer.getElapsedTime() >= m_timeOut; }
        inline void pause() { m_timer.pause(); }
        inline void resume() { m_timer.resume(); }
        inline void switchPause() { m_timer.switchPause(); }

    private:
        PausableTimer m_timer;
        Time m_timeOut;
        timer_emitter_t m_emitter;
        TimerType m_timerType;
        friend class TimerComponent;
    };

    using TimerConnectorSPtr = sptr<TimerConnector>;

    class TimerComponent : public IComponent
	{
	public:
        TimerConnectorSPtr addTimer(TimerType timerType, Time timeOut, timer_callback_t callback) {
            auto timerConnector(msptr<TimerConnector>(timerType, std::move(timeOut), std::move(callback)));
            m_activeTimers.push_back(timerConnector);
            return timerConnector;
        }

        void update() override;
        void pause();
        void resume();
        void switchPause();

    private:
        vector_shared_pointers<TimerConnector> m_activeTimers;
	};
}

#endif
