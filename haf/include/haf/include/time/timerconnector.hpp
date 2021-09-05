#ifndef HAF_COMPONENT_TIMER_CONNECTOR_COMPONENTEMENT_INCLUDE_HPP
#define HAF_COMPONENT_TIMER_CONNECTOR_COMPONENTEMENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/connection.hpp>
#include <haf/include/time/timepoint.hpp>
#include <haf/include/time/timeview.hpp>
#include <haf/include/time/timer.hpp>
#include <haf/include/time/timertype.hpp>

namespace haf::time
{
using timer_emitter_t  = htps::emitter<TimePoint>;
using timer_callback_t = timer_emitter_t::emitter_callback_t;

/**
 * @brief Facade class around a @b Timer .
 * Instances of this class will be returned from @b TimerComponent
 * A @b TimerComponent can control all the attached instances to it, this way
 * one can perform pauses and time outs to a group of timers.
 */
class TimerConnector
{
public:
    TimerConnector(htps::uptr<Timer> timer,
                   TimerType timerType,
                   TimePoint timeOut,
                   timer_callback_t emitter) :
        timer_{std::move(timer)},
        m_timeOut{std::move(timeOut)},
        m_emitter{std::move(emitter)},
        m_timerType{timerType}
    {}

    inline bool timeOut() const { return timer_->ellapsed() >= m_timeOut; }
    inline void pause() { timer_->pause(); }
    inline void resume() { timer_->resume(); }
    inline void switchPause() { timer_->switchPause(); }

private:
    htps::uptr<Timer> timer_;
    TimePoint m_timeOut;
    timer_emitter_t m_emitter;
    TimerType m_timerType;
    friend class TimerComponent;
};

using TimerConnectorSPtr = htps::sptr<TimerConnector>;

}  // namespace haf::time

#endif
