#pragma once

#ifndef HAF_CORE_SYSTEM_TIMESYSTEM_INCLUDE_HPP
#define HAF_CORE_SYSTEM_TIMESYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <system/i_include/systembase.hpp>
#include <haf/time/include/timepoint.hpp>

namespace haf::sys
{
class TimeSystem final : public SystemBase
{
public:
    TimeSystem(sys::ISystemProvider& system_provider);
    ~TimeSystem();

    time::TimePoint timeSinceStart() const;
    time::TimePoint now() const;

    void startFrame();
    void endFrame();

    void setAcceleration(const mtps::f32 acceleration);

private:
    struct TimeSystemPrivate;
    mtps::uptr<TimeSystemPrivate> priv_;
};
}  // namespace haf::sys

#endif
