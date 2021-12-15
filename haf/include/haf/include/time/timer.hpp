#ifndef HAF_TIME_TIMER_INCLUDE_HPP
#define HAF_TIME_TIMER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/time/timepoint.hpp>
#include <haf/include/time/timer_data.hpp>

namespace haf::time
{
class ITimeView;
class Timer final
{
public:
    explicit Timer(htps::rptr<ITimeView> time_view) noexcept;
    TimePoint ellapsed() const;
    void pause();
    void resume();
    void switchPause();
    void restart();

    bool isPaused() const noexcept;

private:
    TimerData data_;
};
}  // namespace haf::time

#endif
