#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONSYSTEM_INCLUDE_HPP

#include <lib/system/appservice.hpp>

namespace lib::core
{
    /**
    * This system is intended to be used to simulate behaviours
    * to other systems
    */
    class SimulationSystem final : public AppService
	{
	public:
        SimulationSystem();
        ~SimulationSystem() override;

        void update();

    private:
        class SimulationSystemPrivate;
        uptr<SimulationSystemPrivate> priv_;
    };
}

#endif
