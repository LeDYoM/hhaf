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
Timer::Timer(htps::rptr<ITimeView> time_view) noexcept
{
    data_.itime_view_ = time_view;
    restart();
    data_.is_paused_   = false;
    data_.time_paused_ = TimePoint{};
}

void Timer::restart()
{
    data_.started_at_ = data_.itime_view_->now();
}

TimePoint Timer::ellapsed() const
{
    return (isPaused() ? data_.time_paused_ : data_.itime_view_->now() -
            data_.started_at_);
}

void Timer::pause()
{
    if (!isPaused())
    {
        data_.is_paused_   = true;
        data_.time_paused_ = data_.itime_view_->now();
    }
}

void Timer::resume()
{
    if (isPaused())
    {
        data_.is_paused_ = false;
        data_.started_at_ += (data_.itime_view_->now() - data_.time_paused_);
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

}  // namespace haf::time
