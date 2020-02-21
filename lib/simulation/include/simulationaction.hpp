#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONACTION_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONACTION_INCLUDE_HPP

#include <lib/system/inputsystem.hpp>

#include <lib/input/include/key.hpp>
#include <lib/include/liblog.hpp>
#include <lib/time/include/timepoint.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

namespace lib::sys
{
enum class SimulationActionType : u8
{
    KeyPressed = 0U,
    KeyReleased
};

struct SimulationAction
{
    SimulationActionType type;
    time::TimePoint time_point;
    Key key;

    inline bool timeToLaunch(const time::TimePoint &time_since_start,
        const time::TimePoint &last_triggered) const noexcept
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

inline const Object &operator>>(const Object &obj, SimulationAction &simulation_action)
{
    simulation_action.type = obj["type"].as<SimulationActionType>();
    simulation_action.time_point = time::TimePoint{obj["time_point"].as<time::TimePoint::Rep>()};
    simulation_action.key = obj["key"].as<Key>();

    return obj;
}

inline Object &operator<<(Object &obj, const SimulationAction &simulation_action)
{
    obj.set("type", simulation_action.type);
    obj.set("time_point", simulation_action.time_point.nanoseconds());
    obj.set("key", simulation_action.key);

    return obj;
}

using SimulationActionContainer = vector<SimulationAction>;
using CurrentSimulationActionIterator = SimulationActionContainer::const_iterator;
} // namespace lib::sys

#endif
