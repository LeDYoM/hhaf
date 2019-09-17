#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONACTION_GROUP_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONACTION_GROUP_INCLUDE_HPP

#include "simulationaction.hpp"

#include <lib/include/key.hpp>
#include <lib/include/liblog.hpp>
#include <lib/include/core/timepoint.hpp>

#include <mtypes/include/types.hpp>

namespace lib::core
{
    class SimulationActionGroup
    {
    public:
        SimulationActionGroup() noexcept = default;
        SimulationActionGroup(SimulationActionContainer simulation_action_container)
            : simulation_action_container_{std::move(simulation_action_container)} {}

        void addSimulationActionContainer(SimulationActionContainer simulation_action_container)
        {
            simulation_action_container_.insert(std::move(simulation_action_container_));
        }

        constexpr const SimulationActionContainer &getContainer() const noexcept
        {
            return simulation_action_container_;
        }

        void addKeyStroke(const input::Key key, TimePoint delta_time = TimePoint_as_seconds(0.1f), TimePoint delta_between_events = TimePoint_as_seconds(0.1f))
        {
            simulation_action_container_.push_back({core::SimulationActionType::KeyPressed, delta_time, key});
            simulation_action_container_.push_back({core::SimulationActionType::KeyReleased, delta_between_events, key});
        }

    private:
        SimulationActionContainer simulation_action_container_;
    };
}

#endif
