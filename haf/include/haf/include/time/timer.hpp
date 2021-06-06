#ifndef HAF_TIME_TIMER_INCLUDE_HPP
#define HAF_TIME_TIMER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/time/timepoint.hpp>
#include <haf/include/time/timeview.hpp>

namespace haf::time
{
class Timer final : public TimeView
{
public:
    TimePoint ellapsed() const;
    void pause();
    void resume();
    void switchPause();
    void restart();

    constexpr bool isPaused() const noexcept { return is_paused_; }
    void onAttached() override;

private:
    TimePoint started_at_;
    TimePoint time_paused_;
    bool is_paused_;
};
}  // namespace haf::time

#endif
