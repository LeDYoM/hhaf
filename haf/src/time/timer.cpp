#include <haf/include/time/timer.hpp>
#include <haf/include/time/time_view.hpp>
#include <haf/include/system/subsystem_view.hpp>
#include <haf/include/system/systemaccess.hpp>

namespace
{
auto now(auto const node)
{
    return node->subSystemViewer().subSystem<haf::time::ITimeView>()->now();
}
}  // namespace

namespace haf::time
{
void Timer::restart()
{
    started_at_ = now(attachedNode());
}

TimePoint Timer::ellapsed() const
{
    return ((isPaused() ? time_paused_ : now(attachedNode())) - started_at_);
}

void Timer::pause()
{
    if (!isPaused())
    {
        is_paused_   = true;
        time_paused_ = now(attachedNode());
    }
}

void Timer::resume()
{
    if (isPaused())
    {
        is_paused_ = false;
        started_at_ += (now(attachedNode()) - time_paused_);
    }
}

void Timer::switchPause()
{
    (void)(isPaused() ? resume() : pause());
}

bool Timer::isPaused() const noexcept
{
    return is_paused_;
}

void Timer::onAttached()
{
    restart();
    is_paused_   = false;
    time_paused_ = TimePoint{};
}
}  // namespace haf::time
