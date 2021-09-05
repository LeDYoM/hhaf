#include <haf/include/time/timer.hpp>

namespace haf::time
{
void Timer::restart()
{
    started_at_ = now();
}

TimePoint Timer::ellapsed() const
{
    return ((isPaused() ? time_paused_ : now()) - started_at_);
}

void Timer::pause()
{
    if (!isPaused())
    {
        is_paused_   = true;
        time_paused_ = now();
    }
}

void Timer::resume()
{
    if (isPaused())
    {
        is_paused_ = false;
        started_at_ += (now() - time_paused_);
    }
}

void Timer::switchPause()
{
    (void)(isPaused() ? resume() : pause());
}

void Timer::onAttached()
{
    restart();
    is_paused_   = false;
    time_paused_ = TimePoint{};
}
}  // namespace haf::time
