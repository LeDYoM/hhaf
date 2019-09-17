#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONACTION_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONACTION_INCLUDE_HPP

#include "timesystem.hpp"
#include "inputsystem.hpp"

#include <lib/include/key.hpp>
#include <lib/include/liblog.hpp>
#include <lib/include/core/timepoint.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/simulabledataprovider.hpp>
#include <lib/system/randomsystem.hpp>

#include <mtypes/include/types.hpp>

namespace lib::core
{
    enum class SimulationActionType : u8
    {
        KeyPressed,
        KeyReleased
    };

    struct SimulationAction
    {
        SimulationActionType type;
        TimePoint time_point;
        input::Key key;
        bool relative_time_point{true};

        inline bool timeToLaunch(const TimePoint& time_since_start, const TimePoint& last_triggered) const noexcept
        {
            // To calculate if is time to trigger the action:
            // - Get the time passed since the start.
            // - In case that is time action is relative (to the previous one),
            //   substract the time when the last action was triggered.
            // - If it is not relative, substract nothing.
            // - return if this quantity is bigger than the time_point of this SimulationAction.
            return (time_since_start - (relative_time_point ? last_triggered : TimePoint{})) > time_point;
        }
    };

    using SimulationActionContainer = vector<SimulationAction>;
    using CurrentSimulationActionIterator = SimulationActionContainer::const_iterator;
}

#endif
