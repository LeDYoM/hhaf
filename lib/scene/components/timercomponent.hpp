#pragma once

#ifndef LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP
#define LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/include/core/timepoint.hpp>
#include <lib/facades/include/timeview.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/lockablevector.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/scene/icomponent.hpp>

namespace lib::scene
{
    using timer_emitter_t = emitter<TimePoint>;
    using timer_callback_t = timer_emitter_t::emitter_callback_t;

    enum class TimerType : u8
    {
        Continuous,
        OneShot
    };

    class TimerConnector
    {
    public:
        TimerConnector(uptr<scene::Timer> timer, TimerType timerType, TimePoint timeOut, timer_callback_t emitter)
            : timer_{ std::move(timer) }, m_timeOut{ std::move(timeOut) },
            m_emitter{ std::move(emitter) }, m_timerType{ timerType } {}

        inline bool timeOut() const { return timer_->ellapsed() >= m_timeOut; }
        inline void pause() { timer_->pause(); }
        inline void resume() { timer_->resume(); }
        inline void switchPause() { timer_->switchPause(); }

    private:
        uptr<scene::Timer> timer_;
        TimePoint m_timeOut;
        timer_emitter_t m_emitter;
        TimerType m_timerType;
        friend class TimerComponent;
    };

    using TimerConnectorSPtr = sptr<TimerConnector>;

    class TimerComponent : public IComponent
	{
	public:
        TimerConnectorSPtr addTimer(TimerType timerType, TimePoint timeOut, timer_callback_t callback)
        {
            auto timerConnector(msptr<TimerConnector>(
                attachedNode()->dataWrapper<Timer>(),
                timerType, std::move(timeOut), std::move(callback)));
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
