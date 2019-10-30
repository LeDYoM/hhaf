#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/appservice.hpp>
#include <lib/system/simulabledataprovider.hpp>
#include <lib/system/simulationaction.hpp>
#include <lib/include/core/timepoint.hpp>
#include <lib/system/simulationactiongroup.hpp>

namespace lib::core
{
    /**
    * This system is intended to be used to simulate behaviours
    * to other systems.
    * 
    * For this purpose, the simulation system...
    */
    class SimulationSystem final : public HostedAppService, public ISimulableDataProvider
    {
    public:
        SimulationSystem(core::SystemProvider &system_provider);
        ~SimulationSystem() override;

        void update();
        size_type getNext(const str& name, const size_type min, const size_type max) override;

        void setSimulationActions(const TimePoint &current, SimulationActionGroup simulation_action_group);
        void setSimulationActions(SimulationActionGroup simulation_action_group);
        void setSimulatedDataBuffer(SimulableDataBuffer simulated_data_buffer);
        void initialize();

    private:
        struct SimulationSystemPrivate;
        uptr<SimulationSystemPrivate> priv_;
    };
}

#endif
