#include <haf/time/include/timer.hpp>
#include "timesystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <system/i_include/get_system.hpp>

namespace haf::time
{
void Timer::restart()
{
    started_at_ = sys::getSystem<sys::TimeSystem>(attachedNode()).now();
}

TimePoint Timer::ellapsed() const
{
    if (isPaused())
    {
        return time_paused_ - started_at_;
    }
    else
    {
        return now() - started_at_;
    }
}

void Timer::pause()
{
    if (!isPaused())
    {
        is_paused_ = true;
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
    is_paused_ = false;
    time_paused_ = TimePoint{};
}
} // namespace haf::scene
