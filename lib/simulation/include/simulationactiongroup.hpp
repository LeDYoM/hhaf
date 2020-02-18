#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONACTION_GROUP_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONACTION_GROUP_INCLUDE_HPP

#include "simulationaction.hpp"

#include <lib/include/key.hpp>
#include <lib/time/include/timepoint.hpp>

#include <mtypes/include/types.hpp>

namespace lib::sys
{
    /**
     * This class encapsulates a SimulationActionGroup.
     * 
     */ 
    class SimulationActionGroup
    {
    public:
        /// Default constructor.
        /// Initializes an empty SimulationActionGroup.
        SimulationActionGroup() noexcept = default;

        /// Constructs a SimulationActionGroup given a @b SimulationActionContainer.
        /// @param[in] simulation_action_container The @b SimulationActionContainer to use for
        ///     the initialization.
        SimulationActionGroup(SimulationActionContainer simulation_action_container)
            : simulation_action_container_{std::move(simulation_action_container)} {}

        /// Adds a @b SimulationActionContainer to the container of pending @b SimulationActionContainer (s).
        /// @param[in] simulation_action_container Element to be added.
        void addSimulationActionContainer(SimulationActionContainer simulation_action_container)
        {
            simulation_action_container_.insert(std::move(simulation_action_container_));
        }

        /// Get a constant reference to the inner @b SimulationActionContainer.
        /// @return A const reference to the inner @b SimulationActionContainer.
        constexpr const SimulationActionContainer &getContainer() const noexcept
        {
            return simulation_action_container_;
        }

        /// Add a key stroke to the current internal @b SimulationActionContainer.
        /// To do that, an action of simulated keydown and then simulated key up.
        /// The separation times will be according the parameters.
        /// @param[in] key The @Key to add to the container.
        /// @param[in] delta_time @b TimePoint difference with the previous added event. Default 0.1 seconds
        /// @param[in] delta_between_events @b TimePoint difference within the key down and key up events. Default 0.1 seconds.
        void addKeyStroke(const Key key, TimePoint delta_time = TimePoint_as_seconds(0.1f), TimePoint delta_between_events = TimePoint_as_seconds(0.1f))
        {
            simulation_action_container_.push_back({sys::SimulationActionType::KeyPressed, delta_time, key});
            simulation_action_container_.push_back({sys::SimulationActionType::KeyReleased, delta_between_events, key});
        }

    private:
        SimulationActionContainer simulation_action_container_; ///< Container to store the simulatted actions.
    };
}

#endif
