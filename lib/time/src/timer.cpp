#include <lib/time/include/timer.hpp>

#include <lib/include/liblog.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scenemanager.hpp>
#include <lib/time/i_include/timesystem.hpp>
#include <lib/system/systemprovider.hpp>

namespace lib::time
{
void Timer::restart()
{
    started_at_ = attachedNode()->sceneManager().systemProvider().timeSystem().now();
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
} // namespace lib::scene
