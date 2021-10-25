#ifndef HAF_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP
#define HAF_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include "system/systembase.hpp"
#include <haf/include/simulation/simulationactiongroup.hpp>

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

    void update();
    bool getNext(const htps::str& name, htps::size_type& pre_selected);

    void setSimulationActions(const time::TimePoint& current,
                              SimulationActionGroup simulation_action_group);
    void setSimulationActions(SimulationActionGroup simulation_action_group);
    void setSimulateRandomDataBuffer(
        SimulateRandomDataBuffer simulated_data_buffer);
    void initialize(htps::str const& simulation_input_file,
                    htps::str const& simulation_output_file);

private:
    struct SimulationSystemPrivate;
    htps::uptr<SimulationSystemPrivate> priv_;
};
}  // namespace haf::sys

#endif
