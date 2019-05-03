#include "simulationsystem.hpp"

#include <lib/include/core/log.hpp>

namespace lib::core
{
    SimulationSystem::SimulationSystem(core::SystemProvider &system_provider)
		: HostedAppService{ system_provider }
    {
        
    }

    SimulationSystem::~SimulationSystem() = default;

    void SimulationSystem::update()
    {
    }
}
