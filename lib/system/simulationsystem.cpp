#include "simulationsystem.hpp"
#include "simulationsystem_private.hpp"
#include "simulationaction.hpp"

#include "timesystem.hpp"

#include <lib/include/key.hpp>
#include <lib/include/liblog.hpp>
#include <lib/include/core/timepoint.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/simulabledataprovider.hpp>
#include <lib/system/randomsystem.hpp>
#include <lib/system/filesystem/filesystem.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

#include <fstream>

namespace lib::core
{
    SimulationSystem::SimulationSystem(SystemProvider &system_provider)
        : HostedAppService{ system_provider },
        priv_{ muptr<SimulationSystemPrivate>() } {}

    SimulationSystem::~SimulationSystem()
    {
        constexpr char SaveFileName[] = "simulation_output.txt";

        if (!priv_->replay_data_.data_buffer_.empty())
        {
            log_debug_info("Going to write play data into file " , SaveFileName);
            log_debug_info("Writing play data...");

            Object obj;
            obj << priv_->replay_data_;

            str temp;
            temp << obj;
            if (systemProvider().fileSystem().saveFile(SaveFileName, temp))
            {
                log_debug_info("Play data written successfully");
            }
            else
            {
                log_debug_error("Error while writing the debug data");
            }
        }
        else
        {
            log_debug_info("No file or no data to store the replay");
        }
    }

    void SimulationSystem::initialize()
    {
        static constexpr char InputFileName[] = "simulation_input.txt";

        if (str temp(systemProvider().fileSystem().loadTextFile(InputFileName)); !temp.empty())
        {
            // If the file has been read corretly,
            // createan ObjectCompiler and use it.
            ObjectCompiler obj_compiler(temp);
            if (obj_compiler.compile())
            {
                // The compilation was correct so, at least we
                // have a valid Object.
                obj_compiler.result() >> priv_->replay_data_;
            }
        }
    }

    void SimulationSystem::setSimulationActions(const TimePoint &current, SimulationActionGroup simulation_action_group)
    {
        priv_->setSimulationActions(current, simulation_action_group.getContainer());
    }

    void SimulationSystem::setSimulationActions(SimulationActionGroup simulation_action_group)
    {
        setSimulationActions(systemProvider().timeSystem().now(), simulation_action_group.getContainer());
    }

    void SimulationSystem::setSimulatedDataBuffer(SimulableDataBuffer simulated_data_buffer)
    {
        priv_->setSimulatedDataBuffer(std::move(simulated_data_buffer));
    }

    void SimulationSystem::update()
    {
        // Check if we have still actions to trigger.
        if (priv_->current_simulation_action_iterator_ != priv_->replay_data_.simulation_actions_.cend())
        {
            // Check if we have reached the next TimePoint
            const SimulationAction& simulation_action{*(priv_->current_simulation_action_iterator_)};
            const TimePoint& current_time_point{systemProvider().timeSystem().now()};
            if (simulation_action.timeToLaunch(current_time_point, priv_->last_checked_point_ ))
            {
                priv_->last_checked_point_ = current_time_point;
                ++(priv_->current_simulation_action_iterator_);

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
                    log_debug_error("Unknown SimulationActionType enum value: ", (int)simulation_action.type);
                }
            }
        }
    }

    void SimulationSystem::generateSimulableDataBuffer(SimulableDataBuffer & dest)
    {
        if (!priv_->simulable_data_buffer_.empty() && priv_->current_simulable_data_buffer_iterator != priv_->simulable_data_buffer_.cend())
        {
            dest.resize(1U);
            dest[0U] = *(priv_->current_simulable_data_buffer_iterator++);
            log_debug_info(dest);
        }
        else
        {
            systemProvider().randomSystem().generateSimulableDataBuffer(dest);
        }

        // Store the generated buffer into the play data.
        priv_->replay_data_.data_buffer_.insert(dest);

    }
}
