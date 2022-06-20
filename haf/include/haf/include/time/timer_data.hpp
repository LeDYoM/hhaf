HTPS_PRAGMA_ONCE
#ifndef HAF_TIME_TIMER_DATA_INCLUDE_HPP
#define HAF_TIME_TIMER_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/time/time_point.hpp>

namespace haf::time
{
class ITimeView;
class TimerData final
{
public:
    htps::rptr<ITimeView> itime_view_{nullptr};
    TimePoint started_at_{};
    TimePoint time_paused_{};
    bool is_paused_{false};
};
}  // namespace haf::time

#endif
