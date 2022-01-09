#include <haf/include/time/timer_connector.hpp>

namespace haf::time
{
TimerConnector::TimerConnector(htps::uptr<Timer> timer,
                               TimerType timerType,
                               TimePoint timeOut,
                               timer_callback_t emitter) :
    timer_{std::move(timer)},
    time_out_{std::move(timeOut)},
    emitter_{std::move(emitter)},
    timer_type_{timerType}
{}

bool TimerConnector::timeOut() const
{
    return timer_->ellapsed() >= time_out_;
}

bool TimerConnector::isPaused() const
{
    return timer_->isPaused();
}

void TimerConnector::pause()
{
    timer_->pause();
}

void TimerConnector::resume()
{
    timer_->resume();
}

void TimerConnector::restart()
{
    timer_->restart();
}

void TimerConnector::switchPause()
{
    timer_->switchPause();
}

void TimerConnector::markToDelete()
{
    timer_type_ = TimerType::OneShot;
    emitter_.clear();
}

TimePoint TimerConnector::ellapsed() const
{
    return timer_->ellapsed();
}

}  // namespace haf::time
