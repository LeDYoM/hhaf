#ifndef HAF_SYSTEM_TIMESYSTEM_ACCELERATION_INCLUDE_HPP
#define HAF_SYSTEM_TIMESYSTEM_ACCELERATION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/time/time_point.hpp>

namespace haf::sys
{
#ifdef HAF_ALLOW_ACCELERATION

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

    constexpr time::TimePoint&& accelerate(
        time::TimePoint&& time_point) const noexcept
    {
        if (use_acceleration)
        {
            return std::move(time_point * acceleration_);
        }
        else
        {
            return std::move(time_point);
        }
    }

private:
    AccelerationFactor acceleration_ = 1.0f;
    bool use_acceleration{false};
};
#else

class TimeSystemAcceleration
{
public:
    using AccelerationFactor = htps::f32;

    constexpr void setAcceleration(AccelerationFactor const) const noexcept {}
    constexpr void resetAcceleration() const noexcept {}

    constexpr time::TimePoint&& accelerate(
        time::TimePoint&& time_point) const noexcept
    {
        return std::move(time_point);
    }
};

#endif
}  // namespace haf::sys

#endif
