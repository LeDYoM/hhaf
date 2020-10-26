#include "simulationsystem.hpp"
#include "simulationsystem_private.hpp"
#include <haf/simulation/include/simulationaction.hpp>

#include <haf/input/include/key.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/time/include/timepoint.hpp>
#include <system/i_include/systemprovider.hpp>
#include <system/i_include/systemdatawrappercreator.hpp>
#include <random/i_include/randomsystem.hpp>
#include <time/i_include/timesystem.hpp>
#include <filesystem/i_include/filesystem.hpp>
#include <haf/filesystem/include/fileserializer.hpp>
#include <input/i_include/inputsystem.hpp>

#include <mtypes/include/serializer.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

using namespace mtps;

namespace haf::sys
{
SimulationSystem::SimulationSystem(SystemProvider& system_provider) :
    SystemBase{system_provider}, priv_{muptr<SimulationSystemPrivate>()}
{}

SimulationSystem::~SimulationSystem()
{
    constexpr char SaveFileName[] = "simulation_output.txt";

    DisplayLog::info("Serializing play data...");
    DisplayLog::info("Going to write play data into file ", SaveFileName);

    SystemDataWrapperCreator dwc{*this};
    auto file_serializer = dwc.dataWrapper<FileSerializer>();
    auto const result    = file_serializer->serializeToFile(
        SaveFileName, priv_->next_replay_data_);

    if (result != FileSerializer::Result::Success)
    {
        if (result == FileSerializer::Result::FileIOError)
        {
            DisplayLog::debug("Cannot write ", SaveFileName);
        }
        else if (result == FileSerializer::Result::ParsingError)
        {
            DisplayLog::error("Error parsing oputput for ", SaveFileName);
        }
        else
        {
            DisplayLog::error("Unknow error outputting file: ", SaveFileName);
        }
    }
    else
    {
        DisplayLog::info("Play data written correctly to ", SaveFileName);
    }
}

void SimulationSystem::initialize()
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

    static constexpr char InputFileName[] = "simulation_input.txt";

    DisplayLog::info("Trying to load ", InputFileName,
                     " to read simulation data");
    SystemDataWrapperCreator dwc{*this};
    auto file_serializer = dwc.dataWrapper<FileSerializer>();
    auto const result    = file_serializer->deserializeFromFile(
        InputFileName, priv_->current_replay_data_);

    if (result != FileSerializer::Result::Success)
    {
        if (result == FileSerializer::Result::FileIOError)
        {
            DisplayLog::debug("Simulation file ", InputFileName, " not found");
        }
        else if (result == FileSerializer::Result::ParsingError)
        {
            DisplayLog::error("File ", InputFileName,
                              " found but contains invalid format.");
        }
        else
        {
            DisplayLog::error(
                "Unknow error reading and parsing simulation file: ",
                InputFileName);
        }
    }

    // Prepare output
    priv_->next_last_checked_point_ = systemProvider().timeSystem().now();
    priv_->current_simulation_action_iterator_ =
        priv_->current_replay_data_.simulation_actions_.cbegin();
    priv_->current_simulable_data_buffer_iterator =
        priv_->current_replay_data_.data_buffer_.cbegin();
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
    setSimulationActions(systemProvider().timeSystem().now(),
                         simulation_action_group.getContainer());
}

void SimulationSystem::setSimulateRandomDataBuffer(
    SimulateRandomDataBuffer simulated_data_buffer)
{
    priv_->setSimulateRandomDataBuffer(std::move(simulated_data_buffer));
}

void SimulationSystem::update()
{
    // Get the current TimePoint
    const time::TimePoint& current_time_point{
        systemProvider().timeSystem().now()};

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
                                 KeyIndex(simulation_action.key));
                systemProvider().inputSystem().simulatePressKey(
                    simulation_action.key);
            }
            else if (simulation_action.type ==
                     SimulationActionType::KeyReleased)
            {
                DisplayLog::info("SimulationSystem: releasing key: ",
                                 KeyIndex(simulation_action.key));
                systemProvider().inputSystem().simulateReleaseKey(
                    simulation_action.key);
            }
            else
            {
                DisplayLog::error("Unknown SimulationActionType enum value: ",
                                  (int)simulation_action.type);
            }
        }
    }

    {
        // Check if some new input is there.
        // Note: this will catch the simulated keys in the previous loop too,
        // but
        //      that is intended.
        auto&& input_system{systemProvider().inputSystem()};

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
}

bool SimulationSystem::getNext(const str& name, size_type& pre_selected)
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
