#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/appservice.hpp>
#include <lib/system/simulabledataprovider.hpp>

namespace lib::core
{
    /**
    * This system is intended to be used to simulate behaviours
    * to other systems
    */
    class SimulationSystem final : public HostedAppService, public ISimulableDataProvider
    {
    public:
        SimulationSystem(core::SystemProvider &system_provider);
        ~SimulationSystem() override;

        void update();
        void generateSimulableDataBuffer(SimulableDataBuffer& dest) override;
    private:
        struct SimulationSystemPrivate;
        uptr<SimulationSystemPrivate> priv_;
    };
}

#endif
