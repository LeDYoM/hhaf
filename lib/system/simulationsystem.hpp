#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/appservice.hpp>
#include <lib/system/simulationactiongroup.hpp>

namespace lib::core
{
/**
    * This system is intended to be used to simulate behaviours
    * to other systems.
    * 
    * For this purpose, the simulation system...
    */
class SimulationSystem final : public HostedAppService
{
public:
    using SimulableDataBuffer = vector<size_type>;

    SimulationSystem(core::SystemProvider &system_provider);
    ~SimulationSystem() override;

    void update();
    bool getNext(const str &name, size_type& pre_selected);

    void setSimulationActions(const TimePoint &current, SimulationActionGroup simulation_action_group);
    void setSimulationActions(SimulationActionGroup simulation_action_group);
    void setSimulatedDataBuffer(SimulableDataBuffer simulated_data_buffer);
    void initialize();

private:
    struct SimulationSystemPrivate;
    uptr<SimulationSystemPrivate> priv_;
};
} // namespace lib::core

#endif
