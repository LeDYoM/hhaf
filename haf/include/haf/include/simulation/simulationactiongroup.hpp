HTPS_PRAGMA_ONCE
#ifndef HAF_CORE_SYSTEM_SIMULATIONACTION_GROUP_INCLUDE_HPP
#define HAF_CORE_SYSTEM_SIMULATIONACTION_GROUP_INCLUDE_HPP

#include "simulationaction.hpp"

#include <haf/include/input/key.hpp>
#include <haf/include/time/time_point.hpp>

#include <htypes/include/types.hpp>

namespace haf::sys
{
/**
 * This class encapsulates a SimulationActionGroup.
 */
class SimulationActionGroup
{
public:
    /**
     * @brief Construct a new Simulation Action Group object
     * Default constructor.
     */
    constexpr SimulationActionGroup() noexcept = default;

    /**
     * @brief Construct a new Simulation Action Group object
     *
     * @param[in] simulation_action_container The @b SimulationActionContainer
     * to use for the initialization
     */
    SimulationActionGroup(
        SimulationActionContainer simulation_action_container) :
        simulation_action_container_{htps::move(simulation_action_container)}
    {}

    /**
     * @brief Adds a @b SimulationActionContainer to the container of pending
     * @b SimulationActionContainer (s).
     *
     * @param[in] simulation_action_container Element to be added.
     */
    void addSimulationActionContainer(
        SimulationActionContainer simulation_action_container)
    {
        simulation_action_container_.insert(
            htps::move(simulation_action_container));
    }

    /**
     * @brief Get a constant reference to the inner
     * @b SimulationActionContainer.
     *
     * @return A const reference to the inner @b SimulationActionContainer.
     */
    constexpr const SimulationActionContainer& getContainer() const noexcept
    {
        return simulation_action_container_;
    }

    /**
     * @brief Add a key to the current internal @b SimulationActionContainer.
     * To do that, an action of simulated keydown and then simulated key up.
     * The separation times will be according the arguments.
     *
     * @param[in] key The @b input::Key to add to the container.
     * @param[in] delta_time @b TimePoint difference with the previous added
     * event. Default 0.1 seconds.
     * @param[in] delta_between_events @b TimePoint difference within the
     * key down and key up events. Default 0.1 seconds.
     */
    void addKeyStroke(
        const input::Key key,
        time::TimePoint delta_time = time::TimePoint_as_seconds_f32(0.1f),
        time::TimePoint delta_between_events =
            time::TimePoint_as_seconds_f32(0.1f))
    {
        simulation_action_container_.push_back(
            {sys::SimulationActionType::KeyPressed, delta_time, key});
        simulation_action_container_.push_back(
            {sys::SimulationActionType::KeyReleased, delta_between_events,
             key});
    }

private:
    SimulationActionContainer
        simulation_action_container_;  ///< Container to store the simulatted
                                       ///< actions.
};
}  // namespace haf::sys

#endif
