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
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

namespace lib::core
{
    enum class SimulationActionType : u8
    {
        KeyPressed = 0U,
        KeyReleased
    };

    struct SimulationAction
    {
        SimulationActionType type;
        TimePoint time_point;
        input::Key key;

        inline bool timeToLaunch(const TimePoint& time_since_start, const TimePoint& last_triggered) const noexcept
        {
            // To calculate if is time to trigger the action:
            // - Get the time passed since the start.
            // - In case that is time action is relative (to the previous one),
            //   substract the time when the last action was triggered.
            // - If it is not relative, substract nothing.
            // - return if this quantity is bigger than the time_point of this SimulationAction.
            return ((time_since_start - last_triggered) > time_point);
        }
    };

    inline const Object& operator>>(const Object& obj, SimulationAction& simulation_action)
    {
//        simulation_action.type = static_cast<SimulationActionType>(obj["type"].as<std::underlying_type_t<SimulationActionType>>());
//        simulation_action.time_point = TimePoint{obj["time_point"].as<TimePoint::Rep>()};
//        simulation_action.key = static_cast<input::Key>(obj["type"].as<std::underlying_type_t<input::Key>>());

        return obj;
    }

    inline Object& operator<<(Object& obj, const SimulationAction& simulation_action)
    {
        obj.set("type", static_cast<std::underlying_type_t<SimulationActionType>>(simulation_action.type));
//        obj.set("time_point", simulation_action.time_point.nanoseconds());
//        obj.set("key", static_cast<std::underlying_type_t<input::Key>>(simulation_action.key));

        return obj;
    }

    using SimulationActionContainer = vector<SimulationAction>;
    using CurrentSimulationActionIterator = SimulationActionContainer::const_iterator;
}

#endif
