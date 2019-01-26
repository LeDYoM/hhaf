#include "simulationsystem.hpp"

#include <lib/include/core/log.hpp>

namespace lib::core
{
    class SimulationSystem::SimulationSystemPrivate
    {
    public:
        SimulationSystemPrivate() {}
        ~SimulationSystemPrivate() {}
    };

    SimulationSystem::SimulationSystem()
        : AppService{ }//,
    //    priv_ { muptr<SimulationSystemPrivate>() } 
    {}

    SimulationSystem::~SimulationSystem() = default;

    void SimulationSystem::update()
    {
    }
}
