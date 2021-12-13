#ifndef HAF_TIME_TIMER_DATA_INCLUDE_HPP
#define HAF_TIME_TIMER_DATA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/time/timepoint.hpp>

namespace haf::time
{
class TimerData final
{
public:
    TimePoint started_at_;
    TimePoint time_paused_;
    bool is_paused_;
};
}  // namespace haf::time

#endif
