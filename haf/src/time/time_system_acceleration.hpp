#ifndef HAF_SYSTEM_TIMESYSTEM_ACCELERATION_INCLUDE_HPP
#define HAF_SYSTEM_TIMESYSTEM_ACCELERATION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/time/timepoint.hpp>

namespace haf::sys
{
class TimeSystemAcceleration
{
public:
    using AccelerationFactor = htps::f32;

    constexpr TimeSystemAcceleration() noexcept :
        acceleration_{1.0F}, use_acceleration{false}
    {}

    constexpr void setAcceleration(
        AccelerationFactor const acceleration) noexcept
    {
        use_acceleration = true;
        acceleration_    = acceleration;
    }

    constexpr void resetAcceleration() noexcept
    {
        use_acceleration = false;
        acceleration_    = 1.0F;
    }

    time::TimePoint&& accelerate(time::TimePoint&& time_point) const noexcept
    {
        if (!use_acceleration)
        {
            return std::move(time_point);
        }
        else
        {
            return std::move(time_point * acceleration_);
        }
    }

private:
    AccelerationFactor acceleration_ = 1.0f;
    bool use_acceleration{false};
};


}  // namespace haf::sys

#endif
