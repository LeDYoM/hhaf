#ifndef HAF_COMPONENT_TIMER_CONNECTOR_COMPONENTEMENT_INCLUDE_HPP
#define HAF_COMPONENT_TIMER_CONNECTOR_COMPONENTEMENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/connection.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/time/time_view.hpp>
#include <haf/include/time/timer.hpp>
#include <haf/include/time/timer_type.hpp>

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
class TimerConnector final
{
public:
    TimerConnector(htps::uptr<Timer> timer,
                   TimerType timerType,
                   TimePoint timeOut,
                   timer_callback_t emitter);

    bool timeOut() const;
    bool isPaused() const;
    void pause();
    void resume();
    void restart();
    void switchPause();
    void markToDelete();
    TimePoint ellapsed() const;

private:
    htps::uptr<Timer> timer_;
    TimePoint time_out_;
    timer_emitter_t emitter_;
    TimerType timer_type_;
    friend class TimerComponent;
};

using TimerConnectorSPtr = htps::sptr<TimerConnector>;

}  // namespace haf::time

#endif
