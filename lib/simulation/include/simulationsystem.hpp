#pragma once

#ifndef HAF_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP
#define HAF_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/include/appservice.hpp>
#include <lib/simulation/include/simulationactiongroup.hpp>

namespace haf::sys
{
///
/// This system is intended to be used to simulate behaviours
/// to other systems.
/// For this purpose, the simulation system...
class SimulationSystem final : public AppService
{
public:
    using SimulateRandomDataBuffer = mtps::vector<mtps::size_type>;

    SimulationSystem(sys::SystemProvider &system_provider);
    ~SimulationSystem() override;

    void update();
    bool getNext(const mtps::str&name, mtps::size_type &pre_selected);

    void setSimulationActions(const time::TimePoint &current,
                              SimulationActionGroup simulation_action_group);
    void setSimulationActions(SimulationActionGroup simulation_action_group);
    void setSimulateRandomDataBuffer(SimulateRandomDataBuffer simulated_data_buffer);
    void initialize();

private:
    struct SimulationSystemPrivate;
    mtps::uptr<SimulationSystemPrivate> priv_;
};
} // namespace haf::sys

#endif
