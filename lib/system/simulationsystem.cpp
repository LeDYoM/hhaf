#include "simulationsystem.hpp"
#include "simulationsystem_private.hpp"
#include "simulationaction.hpp"

#include "timesystem.hpp"

#include <lib/include/key.hpp>
#include <lib/include/liblog.hpp>
#include <lib/include/core/timepoint.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/randomsystem.hpp>
#include <lib/system/filesystem/filesystem.hpp>

#include <mtypes/include/serializer.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

namespace lib::core
{
SimulationSystem::SimulationSystem(SystemProvider &system_provider)
    : HostedAppService{system_provider},
      priv_{muptr<SimulationSystemPrivate>()} {}

SimulationSystem::~SimulationSystem()
{
    constexpr char SaveFileName[] = "simulation_output.txt";

    DisplayLog::info("Serializing play data...");

    DisplayLog::info("Going to write play data into file ", SaveFileName);
    if (systemProvider().fileSystem().saveFile(
        SaveFileName,
        Serializer<decltype(priv_->next_replay_data_)>::
            serialize(priv_->next_replay_data_)))
    {
        DisplayLog::info("Play data written successfully");
    }
    else
    {
        DisplayLog::error("Error while writing the debug data");
    }
}

void SimulationSystem::initialize()
{
    // Just test.
    SimulationActionGroup simulation_action_group;

#ifdef LIB_USE_SIMULATION_INIT_DATA
    {
        simulation_action_group.addKeyStroke(input::Key::Return);
        simulation_action_group.addKeyStroke(input::Key::Down);
        simulation_action_group.addKeyStroke(input::Key::Return);

        auto &simulationSystem(systemProvider().simulationSystem());
        simulationSystem.setSimulationActions(simulation_action_group);
        simulationSystem.setSimulateRandomDataBuffer(
            SimulateRandomDataBuffer{0U, 0U, 0U, 0U});
    }
#endif

    static constexpr char InputFileName[] = "simulation_input.txt";

    DisplayLog::info("Trying to load ", InputFileName, " to read simulation data");
    if (str temp(systemProvider().fileSystem().loadTextFile(InputFileName)); !temp.empty())
    {
        // If the file has been read corretly,
        // createan ObjectCompiler and use it.
        ObjectCompiler obj_compiler(temp);
        if (obj_compiler.compile())
        {
            // The compilation was correct so, at least we
            // have a valid Object.
            obj_compiler.result() >> priv_->current_replay_data_;
        }
    }
    else
    {
        DisplayLog::info("File ", InputFileName, " not found");
    }

    // Prepare output
    priv_->next_last_checked_point_ = systemProvider().timeSystem().now();
    priv_->current_simulation_action_iterator_ =
        priv_->current_replay_data_.simulation_actions_.cbegin();
    priv_->current_simulable_data_buffer_iterator = 
        priv_->current_replay_data_.data_buffer_.cbegin();
}

void SimulationSystem::setSimulationActions(const TimePoint &current, SimulationActionGroup simulation_action_group)
{
    priv_->setSimulationActions(current, simulation_action_group.getContainer());
}

void SimulationSystem::setSimulationActions(SimulationActionGroup simulation_action_group)
{
    setSimulationActions(systemProvider().timeSystem().now(), simulation_action_group.getContainer());
}

void SimulationSystem::setSimulateRandomDataBuffer(SimulateRandomDataBuffer simulated_data_buffer)
{
    priv_->setSimulateRandomDataBuffer(std::move(simulated_data_buffer));
}

void SimulationSystem::update()
{
    // Get the current TimePoint
    const TimePoint &current_time_point{systemProvider().timeSystem().now()};

    // Check if we have still actions to trigger.
    if (!priv_->current_replay_data_.simulation_actions_.empty() &&
        (priv_->current_simulation_action_iterator_ !=
         priv_->current_replay_data_.simulation_actions_.cend()))
    {
        // Check if we have reached the next TimePoint
        const SimulationAction &simulation_action{*(priv_->current_simulation_action_iterator_)};
        if (simulation_action.timeToLaunch(current_time_point, priv_->current_last_checked_point_))
        {
            priv_->current_last_checked_point_ = current_time_point;
            ++(priv_->current_simulation_action_iterator_);

            if (simulation_action.type == SimulationActionType::KeyPressed)
            {
                DisplayLog::info("SimulationSystem: Pressing key: ", KeyIndex(simulation_action.key));
                systemProvider().inputSystem().simulatePressKey(simulation_action.key);
            }
            else if (simulation_action.type == SimulationActionType::KeyReleased)
            {
                DisplayLog::info("SimulationSystem: releasing key: ", KeyIndex(simulation_action.key));
                systemProvider().inputSystem().simulateReleaseKey(simulation_action.key);
            }
            else
            {
                DisplayLog::error("Unknown SimulationActionType enum value: ", (int)simulation_action.type);
            }
        }
    }

    {
        // Check if some new input is there.
        // Note: this will catch the simulated keys in the previous loop too, but
        //      that is intended.
        auto &&input_system{systemProvider().inputSystem()};

        // If there are keys pending in the input system, process them.
        if (
            !input_system.pressedKeys().empty() ||
            !input_system.releasedKeys().empty())
        {
            for (const auto &pressedKey : input_system.pressedKeys())
            {
                SimulationAction simulation_action{
                    SimulationActionType::KeyPressed,
                    (current_time_point - priv_->next_last_checked_point_),
                    pressedKey};
                priv_->addSimulationAction(std::move(simulation_action));
            }

            for (const auto &releasedKey : input_system.releasedKeys())
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

bool SimulationSystem::getNext(const str &name, size_type &pre_selected)
{
    bool generated{false};

    if (!priv_->current_replay_data_.data_buffer_.empty() &&
        priv_->current_simulable_data_buffer_iterator != priv_->current_replay_data_.data_buffer_.cend())
    {
        pre_selected = (*(priv_->current_simulable_data_buffer_iterator++));
        generated = true;
        DisplayLog::info("Returning simulated data: ", pre_selected);
    }

    // Store the generated buffer into the play data.
    priv_->next_replay_data_.data_buffer_.push_back(pre_selected);
    DisplayLog::info("Generated data added to buffer for ", name);
    return generated;
}
} // namespace lib::core
