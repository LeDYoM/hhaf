#pragma once

#ifndef LIB_COMPONENT_TIMER_CONNECTOR_COMPONENTEMENT_INCLUDE_HPP
#define LIB_COMPONENT_TIMER_CONNECTOR_COMPONENTEMENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/time/include/timepoint.hpp>
#include <lib/time/include/timeview.hpp>
#include <lib/time/include/timer.hpp>
#include <lib/time/include/timertype.hpp>

namespace lib::time
{
using timer_emitter_t = emitter<TimePoint>;
using timer_callback_t = timer_emitter_t::emitter_callback_t;

class TimerConnector
{
public:
    TimerConnector(uptr<Timer> timer, TimerType timerType, TimePoint timeOut, timer_callback_t emitter)
        : timer_{std::move(timer)}, m_timeOut{std::move(timeOut)},
          m_emitter{std::move(emitter)}, m_timerType{timerType} {}

    inline bool timeOut() const { return timer_->ellapsed() >= m_timeOut; }
    inline void pause() { timer_->pause(); }
    inline void resume() { timer_->resume(); }
    inline void switchPause() { timer_->switchPause(); }

private:
    uptr<Timer> timer_;
    TimePoint m_timeOut;
    timer_emitter_t m_emitter;
    TimerType m_timerType;
    friend class TimerComponent;
};

using TimerConnectorSPtr = sptr<TimerConnector>;

} // namespace lib::time

#endif
