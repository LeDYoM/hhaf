#ifndef HAF_SYSTEM_TIMESYSTEM_INCLUDE_HPP
#define HAF_SYSTEM_TIMESYSTEM_INCLUDE_HPP

#include "system/systembase.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/time/timepoint.hpp>

namespace haf::sys
{
/**
 * @brief System class to manage everything related to time.
 */
class TimeSystem final : public SystemBase
{
public:
    /**
     * @brief Construct a new Time System object
     * @param system_provider The system provider instance
     */
    explicit TimeSystem(sys::ISystemProvider& system_provider);

    /**
     * @brief Destroy the Time System object
     */
    ~TimeSystem();

    time::TimePoint timeSinceStart() const;
    time::TimePoint now() const;
    time::TimePoint lastFrameTime() const;
    void startFrame();
    void endFrame();

    void setAcceleration(htps::f32 const acceleration);

private:
    struct TimeSystemPrivate;
    htps::uptr<TimeSystemPrivate> priv_;
};
}  // namespace haf::sys

#endif
