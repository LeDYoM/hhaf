#ifndef HAF_CORE_SYSTEM_TIMESYSTEM_INCLUDE_HPP
#define HAF_CORE_SYSTEM_TIMESYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <system/i_include/systembase.hpp>
#include <haf/time/include/timepoint.hpp>

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
    TimeSystem(sys::ISystemProvider& system_provider);
    ~TimeSystem();

    time::TimePoint timeSinceStart() const;
    time::TimePoint now() const;

    void startFrame();
    void endFrame();

    void setAcceleration(mtps::f32 const acceleration);

private:
    struct TimeSystemPrivate;
    mtps::uptr<TimeSystemPrivate> priv_;
};
}  // namespace haf::sys

#endif
