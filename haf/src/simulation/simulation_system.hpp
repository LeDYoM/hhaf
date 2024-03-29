HTPS_PRAGMA_ONCE
#ifndef HAF_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP
#define HAF_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include "system/system_base.hpp"
#include <haf/include/simulation/simulationactiongroup.hpp>
#include "simulation/simulation_system_configuration.hpp"

namespace haf::sys
{
/**
 * @brief This system is intended to be used to simulate behaviours
 * to other systems.
 * For this purpose, the simulation system provides an interface to add
 * actions to be simulated and add data to different system to force or
 * reproduce a set of different behaviours.
 */
class SimulationSystem final : public SystemBase
{
public:
    using SimulateRandomDataBuffer = htps::vector<htps::size_type>;

    SimulationSystem(SystemProvider& system_provider);
    ~SimulationSystem();

    /**
     * @brief Initialize the Simulation system. It should not be used before
     * calling this function
     * @param simulation_config_file Name of the configuration file to use. If
     * you do not want the simulation system to do anything, pass an empty str
     */
    void initialize(htps::str const& simulation_config_file);

    void updateSimulationInput();
    void updateSimulationOutput();

    bool getNext(htps::str const& name, htps::size_type& pre_selected);

    void setSimulationActions(const time::TimePoint& current,
                              SimulationActionGroup simulation_action_group);
    void setSimulationActions(SimulationActionGroup simulation_action_group);
    void setSimulateRandomDataBuffer(
        SimulateRandomDataBuffer simulated_data_buffer);

private:
    SimulationSystemConfiguration simulation_system_configuration_;
    struct SimulationSystemPrivate;
    htps::uptr<SimulationSystemPrivate> priv_;
};
}  // namespace haf::sys

#endif
