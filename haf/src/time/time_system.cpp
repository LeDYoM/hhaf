#include "time_system.hpp"

#include "time_system_acceleration.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/time/time_point.hpp>
#include "utils/compile_time_constants.hpp"

#include <chrono>

using namespace haf::core;

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
        logger::DisplayLog::info("TimeSystem started at: ", globalStart_.seconds());
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
    void incrementFrame() noexcept { ++m_currentFrame; }

    TimePoint lastFrameTime() const noexcept { return last_frame_time_; }
    TimePoint lastStartFrame() const noexcept { return last_start_frame_; }
    FrameNumberType currentFrame() const noexcept { return m_currentFrame; }

private:
    TimePoint globalStart_;
    TimePoint last_frame_time_{0U};
    TimePoint last_start_frame_{0U};
    TimePoint last_end_frame_{0U};
    FrameNumberType m_currentFrame{0UL};
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

void TimeSystem::preUpdate()
{
    priv_->incrementFrame();
    priv_->updateStartFrameTime();
}

void TimeSystem::postUpdate()
{
    priv_->updateEndFrameTime();
}

TimePoint TimeSystem::lastFrameTime() const noexcept
{
    return priv_->lastFrameTime();
}

time::TimePoint TimeSystem::nowFrame() const noexcept
{
    return priv_->lastStartFrame();
}

FrameNumberType TimeSystem::currentFrame() const noexcept
{
    return priv_->currentFrame();
}

}  // namespace haf::sys
