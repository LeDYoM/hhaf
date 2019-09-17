#include "timesystem.hpp"

#include <chrono>

#include <lib/include/liblog.hpp>
#include <lib/include/core/timepoint.hpp>

namespace lib::core
{
    namespace
    {
        using clock_t = std::chrono::high_resolution_clock;

        constexpr TimePoint timepoint_global_now()
        {
            return TimePoint{static_cast<u64>(clock_t::now().time_since_epoch().count())};
        }
    }

    struct TimeSystem::TimeSystemPrivate final
    {
        TimeSystemPrivate()
        : globalStart_{timepoint_global_now()}
        {
            log_debug_info("TimeSystem started at: ", globalStart_.seconds());
        }

        ~TimeSystemPrivate() {}

        TimePoint timeSinceStart() const
        {
            return (timepoint_global_now() - globalStart_) /* * 100U*/;
        }

        void updateStartFrameTime()
        {
            last_start_frame_ = timepoint_global_now();
        }

        void updateEndFrameTime()
        {
            last_end_frame_ = timepoint_global_now();
        }
    private:
        TimePoint globalStart_;
        TimePoint last_start_frame_{0U};
        TimePoint last_end_frame_{0U};
    };

    TimeSystem::TimeSystem()
        : AppService{ },
        priv_ { muptr<TimeSystemPrivate>() } 
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

    void TimeSystem::startFrame()
    {
        priv_->updateStartFrameTime();
    }

    void TimeSystem::endFrame()
    {
        priv_->updateEndFrameTime();
    }
}
