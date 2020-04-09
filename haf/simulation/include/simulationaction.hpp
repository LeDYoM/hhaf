#pragma once

#ifndef HAF_CORE_SYSTEM_SIMULATIONACTION_INCLUDE_HPP
#define HAF_CORE_SYSTEM_SIMULATIONACTION_INCLUDE_HPP

#include <haf/input/include/key.hpp>
#include <haf/include/liblog.hpp>
#include <haf/time/include/timepoint.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

namespace haf::sys
{
enum class SimulationActionType : mtps::u8
{
    KeyPressed = 0U,
    KeyReleased
};

struct SimulationAction
{
    SimulationActionType type;
    time::TimePoint time_point;
    input::Key key;

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

inline const  mtps::Object&operator>>(const  mtps::Object&obj, SimulationAction &simulation_action)
{
    simulation_action.type = obj["type"].as<SimulationActionType>();
    simulation_action.time_point = time::TimePoint{obj["time_point"].as<time::TimePoint::Rep>()};
    simulation_action.key = obj["key"].as<input::Key>();

    return obj;
}

inline  mtps::Object&operator<<( mtps::Object&obj, const SimulationAction &simulation_action)
{
    obj.set("type", simulation_action.type);
    obj.set("time_point", simulation_action.time_point.nanoseconds());
    obj.set("key", simulation_action.key);

    return obj;
}

using SimulationActionContainer = mtps::vector<SimulationAction>;
using CurrentSimulationActionIterator = SimulationActionContainer::const_iterator;
} // namespace haf::sys

#endif
