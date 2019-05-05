#include "simulationsystem.hpp"

#include <lib/include/core/log.hpp>
#include <mtypes/include/types.hpp>

namespace lib::core
{
    enum class SimulationActionType : u8
    {

    };

    struct SimulationAction
    {
        
    };

    struct SimulationSystem::SimulationSystemPrivate final
    {

    };

    SimulationSystem::SimulationSystem(core::SystemProvider &system_provider)
		: HostedAppService{ system_provider }, priv_{ muptr<SimulationSystemPrivate>() }
    {
        
    }

    SimulationSystem::~SimulationSystem() = default;

    void SimulationSystem::update()
    {
    }
}
