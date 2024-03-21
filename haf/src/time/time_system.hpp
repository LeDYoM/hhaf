HAF_PRAGMA_ONCE
#ifndef HAF_SYSTEM_TIMESYSTEM_INCLUDE_HPP
#define HAF_SYSTEM_TIMESYSTEM_INCLUDE_HPP

#include "system/system_base.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/time/time_view.hpp>

namespace haf::sys
{
using FrameNumberType = core::u64;
/**
 * @brief System class to manage everything related to time.
 */
class TimeSystem final : public SystemBase, public time::ITimeView
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

    time::TimePoint now() const override;

    time::TimePoint lastFrameTime() const noexcept;
    time::TimePoint nowFrame() const noexcept;
    FrameNumberType currentFrame() const noexcept;

    void preUpdate();
    void postUpdate();

    void setAcceleration(htps::f32 const acceleration);

private:
    struct TimeSystemPrivate;
    htps::uptr<TimeSystemPrivate> priv_;
};
}  // namespace haf::sys

#endif
