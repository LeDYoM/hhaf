#pragma once

#ifndef LIB_CORE_SYSTEM_TIMESYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_TIMESYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/include/appservice.hpp>
#include <lib/time/include/timepoint.hpp>

namespace lib::sys
{
class TimeSystem final : public AppService
{
public:
    TimeSystem(sys::SystemProvider& system_provider);
    ~TimeSystem() override;

    time::TimePoint timeSinceStart() const;
    time::TimePoint now() const;

    void startFrame();
    void endFrame();

    void setAcceleration(const mtps::f32 acceleration);

private:
    struct TimeSystemPrivate;
    mtps::uptr<TimeSystemPrivate> priv_;
};
} // namespace lib::sys

#endif
