#include "timesystem.hpp"

#include <chrono>

#include <lib/include/liblog.hpp>
#include <lib/time/include/timepoint.hpp>

namespace lib::sys
{
using namespace time;

namespace
{
using clock_t = std::chrono::high_resolution_clock;

constexpr TimePoint timepoint_global_now()
{
    return TimePoint{static_cast<u64>(clock_t::now().time_since_epoch().count())};
}
} // namespace

struct TimeSystem::TimeSystemPrivate final
{
    TimeSystemPrivate()
        : globalStart_{timepoint_global_now()}
    {
        DisplayLog::info("TimeSystem started at: ", globalStart_.seconds());
    }

    ~TimeSystemPrivate() {}

    TimePoint timeSinceStart() const
    {
        return (timepoint_global_now() - globalStart_)
#ifdef LIB_ALLOW_ACCELERATION
               * acceleration_;
#endif
        ;
    }

    void updateStartFrameTime()
    {
        last_start_frame_ = timepoint_global_now();
    }

    void updateEndFrameTime()
    {
        last_end_frame_ = timepoint_global_now();
    }

#ifdef LIB_ALLOW_ACCELERATION
    void setAcceleration(const f32 acceleration) noexcept
    {
        acceleration_ = acceleration;
    }
#endif
private:
    TimePoint globalStart_;
    TimePoint last_start_frame_{0U};
    TimePoint last_end_frame_{0U};
#ifdef LIB_ALLOW_ACCELERATION
    f32 acceleration_ = 1.0f;
#endif
};

TimeSystem::TimeSystem(sys::SystemProvider& system_provider)
    : HostedAppService{system_provider},
      priv_{muptr<TimeSystemPrivate>()}
{
}

TimeSystem::~TimeSystem() = default;

TimePoint TimeSystem::timeSinceStart() const
{
    return priv_->timeSinceStart();
}

TimePoint TimeSystem::now() const
{
    return priv_->timeSinceStart();
}

void TimeSystem::setAcceleration(const f32 acceleration)
{
#ifdef LIB_ALLOW_ACCELERATION
    priv_->setAcceleration(acceleration);
#endif
}

void TimeSystem::startFrame()
{
    priv_->updateStartFrameTime();
}

void TimeSystem::endFrame()
{
    priv_->updateEndFrameTime();
}
} // namespace lib::sys
