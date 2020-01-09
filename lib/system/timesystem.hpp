#pragma once

#ifndef LIB_CORE_SYSTEM_TIMESYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_TIMESYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/appservice.hpp>
#include <lib/include/core/timepoint.hpp>

namespace lib::sys
{
    class TimeSystem final : public AppService
    {
    public:
        TimeSystem();
        ~TimeSystem() override;

        TimePoint timeSinceStart() const;
        TimePoint now() const;

        void startFrame();
        void endFrame();

        void setAcceleration(const f32 acceleration);

    private:
        struct TimeSystemPrivate;
        uptr<TimeSystemPrivate> priv_;
    };
}

#endif
