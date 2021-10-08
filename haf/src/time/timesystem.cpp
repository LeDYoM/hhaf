#include "timesystem.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/time/timepoint.hpp>

#include <chrono>

using namespace htps;

namespace haf::sys
{
using namespace time;

namespace
{
using clock_t = std::chrono::high_resolution_clock;

TimePoint timepoint_global_now()
{
    return TimePoint{
        static_cast<u64>(clock_t::now().time_since_epoch().count())};
}
}  // namespace

struct TimeSystem::TimeSystemPrivate final
{
    TimeSystemPrivate() : globalStart_{timepoint_global_now()}
    {
        DisplayLog::info("TimeSystem started at: ", globalStart_.seconds());
    }

    TimePoint timeSinceStart() const
    {
#ifdef HAF_ALLOW_ACCELERATION
        TimePoint temp{(timepoint_global_now() - globalStart_)};
        if (!use_acceleration)
        {
            return temp;
        }
        else
        {
            return temp * acceleration_;
        }
#else
        return (timepoint_global_now() - globalStart_);
#endif
    }

    void updateStartFrameTime()
    {
        auto const tmp_start_frame_{last_start_frame_};
        last_start_frame_ = timepoint_global_now();
        last_frame_time_  = last_start_frame_ - tmp_start_frame_;
    }

    void updateEndFrameTime() { last_end_frame_ = timepoint_global_now(); }

    TimePoint lastFrameTime() const noexcept { return last_frame_time_; }
#ifdef HAF_ALLOW_ACCELERATION
    void setAcceleration(f32 const acceleration) noexcept
    {
        use_acceleration = true;
        acceleration_    = acceleration;
    }
#endif
private:
    TimePoint globalStart_;
    TimePoint last_frame_time_{0U};
    TimePoint last_start_frame_{0U};
    TimePoint last_end_frame_{0U};
#ifdef HAF_ALLOW_ACCELERATION
    f32 acceleration_ = 1.0f;
    bool use_acceleration{false};
#endif
};

TimeSystem::TimeSystem(sys::ISystemProvider& system_provider) :
    SystemBase{system_provider}, priv_{muptr<TimeSystemPrivate>()}
{}

TimeSystem::~TimeSystem() = default;

TimePoint TimeSystem::timeSinceStart() const
{
    return priv_->timeSinceStart();
}

TimePoint TimeSystem::now() const
{
    return priv_->timeSinceStart();
}

void TimeSystem::setAcceleration(f32 const acceleration)
{
#ifdef HAF_ALLOW_ACCELERATION
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

TimePoint TimeSystem::lastFrameTime() const
{
    return priv_->lastFrameTime();
}

}  // namespace haf::sys
