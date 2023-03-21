#include "time_system.hpp"

#include "time_system_acceleration.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/time/time_point.hpp>
#include "utils/compile_time_constants.hpp"

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

struct TimeSystem::TimeSystemPrivate final : public TimeSystemAcceleration
{
    TimeSystemPrivate() :
        TimeSystemAcceleration{}, globalStart_{timepoint_global_now()}
    {
        DisplayLog::info("TimeSystem started at: ", globalStart_.seconds());
    }

    TimePoint timeSinceStart() const
    {
        if constexpr (ctc::AllowAcceleration)
        {
            return accelerate(timepoint_global_now() - globalStart_);
        }
        else
        {
            return timepoint_global_now() - globalStart_;
        }
    }

    void updateStartFrameTime()
    {
        auto const tmp_start_frame_{last_start_frame_};
        last_start_frame_ = timeSinceStart();
        last_frame_time_  = last_start_frame_ - tmp_start_frame_;
    }

    void updateEndFrameTime() { last_end_frame_ = timeSinceStart(); }

    TimePoint lastFrameTime() const noexcept { return last_frame_time_; }
    TimePoint lastStartFrame() const noexcept { return last_start_frame_; }

private:
    TimePoint globalStart_;
    TimePoint last_frame_time_{0U};
    TimePoint last_start_frame_{0U};
    TimePoint last_end_frame_{0U};
};

TimeSystem::TimeSystem(sys::ISystemProvider& system_provider) :
    SystemBase{system_provider}, priv_{muptr<TimeSystemPrivate>()}
{}

TimeSystem::~TimeSystem() = default;

TimePoint TimeSystem::now() const
{
    return priv_->timeSinceStart();
}

void TimeSystem::setAcceleration(f32 const acceleration)
{
    if constexpr (ctc::AllowAcceleration)
    {
        priv_->setAcceleration(acceleration);
    }
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

time::TimePoint TimeSystem::nowFrame() const
{
    return priv_->lastStartFrame();
}

}  // namespace haf::sys
