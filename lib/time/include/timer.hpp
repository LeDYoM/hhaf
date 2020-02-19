#pragma once

#ifndef LIB_TIME_TIMER_INCLUDE_HPP
#define LIB_TIME_TIMER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/time/include/timepoint.hpp>
#include <lib/time/include/timeview.hpp>

namespace lib::time
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
} // namespace lib::time

#endif
