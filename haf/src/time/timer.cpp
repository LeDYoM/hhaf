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
    data_.started_at_ = now(attachedNode());
}

TimePoint Timer::ellapsed() const
{
    return ((isPaused() ? data_.time_paused_ : now(attachedNode())) - data_.started_at_);
}

void Timer::pause()
{
    if (!isPaused())
    {
        data_.is_paused_   = true;
        data_.time_paused_ = now(attachedNode());
    }
}

void Timer::resume()
{
    if (isPaused())
    {
        data_.is_paused_ = false;
        data_.started_at_ += (now(attachedNode()) - data_.time_paused_);
    }
}

void Timer::switchPause()
{
    (void)(isPaused() ? resume() : pause());
}

bool Timer::isPaused() const noexcept
{
    return data_.is_paused_;
}

void Timer::onAttached()
{
    restart();
    data_.is_paused_   = false;
    data_.time_paused_ = TimePoint{};
}
}  // namespace haf::time
