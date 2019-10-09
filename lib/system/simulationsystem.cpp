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

#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>

#include <fstream>

namespace lib::core
{
    SimulationSystem::SimulationSystem(SystemProvider &system_provider)
        : HostedAppService{ system_provider },
        priv_{ muptr<SimulationSystemPrivate>() } {}

    SimulationSystem::~SimulationSystem()
    {
        // Test
        priv_->replay_data_.replay_file = "foo2.txt";
        priv_->replay_data_.data_buffer_.push_back(12344U);
        priv_->replay_data_.data_buffer_.push_back(3434U);

        Object obj;
//        obj.set(priv_->replay_data_.data_buffer_);

        if (!priv_->replay_data_.replay_file.empty() && !priv_->replay_data_.data_buffer_.empty())
        {
            log_debug_info("Going to write play data into file " ,priv_->replay_data_.replay_file);
            if (std::ofstream output_file(priv_->replay_data_.replay_file.c_str()); output_file)
            {
                log_debug_info("Writing play data...");
                for (const auto& data : priv_->replay_data_.data_buffer_)
                {
                    output_file << data;
                    if (&data != std::prev(priv_->replay_data_.data_buffer_.end()))
                    {
                        output_file << ",";
                    }
                }
                if (output_file.good())
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
                log_debug_error("Cannot open ", priv_->replay_data_.replay_file," for writing!");
            }
        }
        else
        {
            log_debug_info("No file or no data to store the replay");
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
        if (priv_->current_simulation_action_iterator_ != priv_->simulation_actions_.cend())
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

    void SimulationSystem::setReplayDataFile(str replay_file)
    {
        priv_->replay_data_.replay_file = std::move(replay_file);
    }

    void SimulationSystem::setPlayedDataFile(str played_file)
    {
        priv_->replay_data_.input_replay_file = std::move(played_file);
/*
        if (!priv_->replay_data_.input_replay_file.empty())
        {
            log_debug_info("Going to read play data from file " ,priv_->replay_data_.input_replay_file);
            for (std::ifstream input_file(priv_->replay_data_.replay_file.c_str()); input_file && !input_file.eof();)
            {
                std::string buffer;
                std::getline(input_file,buffer,",");
                for (const auto& data : priv_->replay_data_.data_buffer_)
                {
                    input_file 
                    output_file << data;
                    if (&data != std::prev(priv_->replay_data_.data_buffer_.end()))
                    {
                        output_file << ",";
                    }
                }
                if (output_file.good())
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
                log_debug_error("Cannot open ", priv_->replay_data_.replay_file," for reading!");
            }
        }
        else
        {
            log_debug_info("No file or no data to store the replay");
        }
        */
    }
}
