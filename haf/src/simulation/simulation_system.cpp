#include "simulation_system.hpp"
#include "simulation_system_private.hpp"
#include <haf/include/simulation/simulationaction.hpp>

#include <haf/include/input/key.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/filesystem/ifile_serializer.hpp>

#include <htypes/include/serializer.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/object.hpp>
#include <htypes/include/object_utils.hpp>

#include "random/randomsystem.hpp"
#include "time/time_system.hpp"
#include "filesystem/file_system.hpp"
#include "input/input_system.hpp"

using namespace htps;

namespace haf::sys
{
SimulationSystem::SimulationSystem(SystemProvider& system_provider) :
    SystemBase{system_provider}, priv_{muptr<SimulationSystemPrivate>()}
{}

SimulationSystem::~SimulationSystem()
{
    if (simulation_system_configuration_.useOutputSimulation())
    {
        DisplayLog::info("Serializing play data...");
        DisplayLog::info(
            "Going to write play data into file ",
            simulation_system_configuration_.simulationOutputFileName());

        auto file_serializer{
            subSystemViewer().subSystem<sys::IFileSerializer>()};
        auto const result = file_serializer->serializeToFile(
            simulation_system_configuration_.simulationOutputFileName(),
            priv_->next_replay_data_);

        if (result != IFileSerializer::Result::Success)
        {
            if (result == IFileSerializer::Result::FileIOError)
            {
                DisplayLog::debug("Cannot write ",
                                  simulation_system_configuration_
                                      .simulationOutputFileName());
            }
            else if (result == IFileSerializer::Result::ParsingError)
            {
                DisplayLog::error("Error parsing oputput for ",
                                  simulation_system_configuration_
                                      .simulationOutputFileName());
            }
            else
            {
                DisplayLog::error("Unknow error outputting file: ",
                                  simulation_system_configuration_
                                      .simulationOutputFileName());
            }
        }
        else
        {
            DisplayLog::info(
                "Play data written correctly to ",
                simulation_system_configuration_.simulationOutputFileName());
        }
    }
    else
    {
        DisplayLog::debug("Not writing output simulation. Filename not set");
    }
}

void SimulationSystem::initialize(str const& simulation_config_file_name)
{
    simulation_system_configuration_.loadConfiguration(
        subSystemViewer(), simulation_config_file_name);

    if (simulation_system_configuration_.useInputSimulation())
    {
        // Just test.
        SimulationActionGroup simulation_action_group;

#if 0
        {
            simulation_action_group.addKeyStroke(Key::Return);
            simulation_action_group.addKeyStroke(Key::Down);
            simulation_action_group.addKeyStroke(Key::Return);

            auto &simulationSystem(systemProvider().simulationSystem());
            simulationSystem.setSimulationActions(simulation_action_group);
            simulationSystem.setSimulateRandomDataBuffer(
                SimulateRandomDataBuffer{0U, 0U, 0U, 0U});
        }
#endif

        DisplayLog::info(
            "Trying to load ",
            simulation_system_configuration_.simulationInputFileName(),
            " to read simulation data");
        auto file_serializer =
            subSystemViewer().subSystem<sys::IFileSerializer>();

        auto const result{file_serializer->deserializeFromFile(
            simulation_system_configuration_.simulationInputFileName(),
            priv_->current_replay_data_)};

        file_serializer->processResult(
            result, "Simulation input file",
            simulation_system_configuration_.simulationInputFileName(), false);

        // This part prepares the output part. So, a file will be used to write
        // the output if the simulation system runs.
        priv_->next_last_checked_point_ =
            systemProvider().system<TimeSystem>().now();
        priv_->current_simulation_action_iterator_ =
            priv_->current_replay_data_.simulation_actions_.cbegin();
        priv_->current_simulable_data_buffer_iterator =
            priv_->current_replay_data_.data_buffer_.cbegin();
    }
    else
    {
        DisplayLog::debug("No simulation input file configured");
    }
}

void SimulationSystem::setSimulationActions(
    const time::TimePoint& current,
    SimulationActionGroup simulation_action_group)
{
    priv_->setSimulationActions(current,
                                simulation_action_group.getContainer());
}

void SimulationSystem::setSimulationActions(
    SimulationActionGroup simulation_action_group)
{
    setSimulationActions(systemProvider().system<TimeSystem>().now(),
                         simulation_action_group.getContainer());
}

void SimulationSystem::setSimulateRandomDataBuffer(
    SimulateRandomDataBuffer simulated_data_buffer)
{
    priv_->setSimulateRandomDataBuffer(std::move(simulated_data_buffer));
}

void SimulationSystem::updateSimulationInput()
{
    // Get the current TimePoint
    time::TimePoint const& current_time_point{
        systemProvider().system<TimeSystem>().now()};

    // Check if we have still actions to trigger.
    if ((!priv_->current_replay_data_.simulation_actions_.empty()) &&
        (priv_->current_simulation_action_iterator_ !=
         priv_->current_replay_data_.simulation_actions_.cend()))
    {
        // Check if we have reached the next TimePoint
        const SimulationAction& simulation_action{
            *(priv_->current_simulation_action_iterator_)};
        if (simulation_action.timeToLaunch(current_time_point,
                                           priv_->current_last_checked_point_))
        {
            priv_->current_last_checked_point_ = current_time_point;
            ++(priv_->current_simulation_action_iterator_);

            if (simulation_action.type == SimulationActionType::KeyPressed)
            {
                DisplayLog::info("SimulationSystem: Pressing key: ",
                                 keyIndex(simulation_action.key));
                systemProvider().system<InputSystem>().simulatePressKey(
                    simulation_action.key);
            }
            else if (simulation_action.type ==
                     SimulationActionType::KeyReleased)
            {
                DisplayLog::info("SimulationSystem: releasing key: ",
                                 keyIndex(simulation_action.key));
                systemProvider().system<InputSystem>().simulateReleaseKey(
                    simulation_action.key);
            }
            else
            {
                DisplayLog::error("Unknown SimulationActionType enum value: ",
                                  (int)simulation_action.type);
            }
        }
    }
}

void SimulationSystem::updateSimulationOutput()
{
    // Get the current TimePoint
    time::TimePoint const& current_time_point{
        systemProvider().system<TimeSystem>().now()};

    // Check if some new input is there.
    // Note: this will catch the simulated keys in the previous loop too,
    // but that is intended.
    auto&& input_system{systemProvider().system<InputSystem>()};

    // If there are keys pending in the input system, process them.
    if (!input_system.pressedKeys().empty() ||
        !input_system.releasedKeys().empty())
    {
        for (const auto& pressedKey : input_system.pressedKeys())
        {
            SimulationAction simulation_action{
                SimulationActionType::KeyPressed,
                (current_time_point - priv_->next_last_checked_point_),
                pressedKey};
            priv_->addSimulationAction(std::move(simulation_action));
        }

        for (const auto& releasedKey : input_system.releasedKeys())
        {
            SimulationAction simulation_action{
                SimulationActionType::KeyReleased,
                (current_time_point - priv_->next_last_checked_point_),
                releasedKey};
            priv_->addSimulationAction(std::move(simulation_action));
        }

        // Update the time of the last update.
        priv_->next_last_checked_point_ = current_time_point;
    }
}

bool SimulationSystem::getNext(str const& name, size_type& pre_selected)
{
    bool generated{false};

    if (!priv_->current_replay_data_.data_buffer_.empty() &&
        priv_->current_simulable_data_buffer_iterator !=
            priv_->current_replay_data_.data_buffer_.cend())
    {
        pre_selected = (*(priv_->current_simulable_data_buffer_iterator++));
        generated    = true;
        DisplayLog::info("Returning simulated data: ", pre_selected);
    }

    // Store the generated buffer into the play data.
    priv_->next_replay_data_.data_buffer_.push_back(pre_selected);
    DisplayLog::info("Generated data added to buffer for ", name);
    return generated;
}
}  // namespace haf::sys
