#include "simulationsystem.hpp"

#include "timesystem.hpp"
#include "inputsystem.hpp"

#include <lib/include/key.hpp>
#include <logger/include/log.hpp>
#include <lib/include/core/timer.hpp>

#include <mtypes/include/types.hpp>

namespace lib::core
{
    enum class SimulationActionType : u8
    {
        KeyPressed,
        KeyReleased
    };

    struct SimulationAction
    {
        SimulationActionType type;
        TimePoint tp;
        input::Key key;
    };

    using SimulationActionContainer = vector<SimulationAction>;
    using CurrentSimulationActionIterator = SimulationActionContainer::const_iterator;

    struct SimulationSystem::SimulationSystemPrivate final
    {
        SimulationActionContainer simulation_actions_;
        CurrentSimulationActionIterator current_simulation_action_iterator_;
        TimePoint start_point_;

        void setSimulationActions(const TimePoint now, SimulationActionContainer sim_act_container)
        {
            simulation_actions_.swap(sim_act_container);
            current_simulation_action_iterator_ = simulation_actions_.cbegin();
            start_point_ = now;
            log_debug_info("Simulation System started at: ", start_point_);
        }
    };

    SimulationSystem::SimulationSystem(core::SystemProvider &system_provider)
		: HostedAppService{ system_provider }, priv_{ muptr<SimulationSystemPrivate>() }
    {
        priv_->setSimulationActions(systemProvider().timeSystem().now(),
            {
                {SimulationActionType::KeyPressed, TimePoint_as_seconds(2U), input::Key::Down},
                {SimulationActionType::KeyReleased, TimePoint_as_seconds(3U), input::Key::Down}
            });
    }

    SimulationSystem::~SimulationSystem() = default;

    void SimulationSystem::update()
    {
        // Check if we have reached the next TimePoint
        // And we are not at the end
        if (priv_->current_simulation_action_iterator_ != priv_->simulation_actions_.cend())
        {
            const SimulationAction& simulation_action{*(priv_->current_simulation_action_iterator_)};
            if (systemProvider().timeSystem().now().milliseconds() > simulation_action.tp.milliseconds())
            {
                ++priv_->current_simulation_action_iterator_;

                if (simulation_action.type == SimulationActionType::KeyPressed)
                {
                    log_debug_info("SimulationSystem: Pressing key: ", simulation_action.key);
                    systemProvider().inputSystem().pressKey(simulation_action.key);
                }
                else if (simulation_action.type == SimulationActionType::KeyReleased)
                {
                    log_debug_info("SimulationSystem: releasing key: ", simulation_action.key);
                    systemProvider().inputSystem().releaseKey(simulation_action.key);
                }
                else
                {
                    log_debug_error("Unknown SimulationActionType enum value: ",(int)simulation_action.type);
                }
                
            }
        }
    }
}
