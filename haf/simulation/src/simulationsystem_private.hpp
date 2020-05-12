#pragma once

#ifndef HAF_CORE_SYSTEM_SIMULATIONSYSTEM_PRIVATE_INCLUDE_HPP
#define HAF_CORE_SYSTEM_SIMULATIONSYSTEM_PRIVATE_INCLUDE_HPP

#include <haf/simulation/include/simulationsystem.hpp>
#include <haf/simulation/include/simulationaction.hpp>

#include <haf/input/include/key.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/time/include/timepoint.hpp>
#include <system/i_include/systemprovider.hpp>
#include <random/i_include/randomsystem.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

namespace haf::sys
{

struct ReplayData
{
    SimulationSystem::SimulateRandomDataBuffer data_buffer_;
    SimulationActionContainer simulation_actions_;

    constexpr static char DataBufferName[] = "replay_data";
    constexpr static char InputDataName[]  = "input_data";
};

const mtps::Object& operator>>(const mtps::Object& obj, ReplayData& replay_data)
{
    if (const auto obj_random_generator_data = obj[ReplayData::DataBufferName];
        obj_random_generator_data.isObject())
    {
        obj_random_generator_data.getObject() >> replay_data.data_buffer_;
    }

    if (const auto obj_input_data = obj[ReplayData::InputDataName];
        obj_input_data.isObject())
    {
        obj_input_data.getObject() >> replay_data.simulation_actions_;
    }

    return obj;
}

inline mtps::Object& operator<<(mtps::Object& obj,
                                const ReplayData& replay_data)
{
    obj.set(ReplayData::DataBufferName, replay_data.data_buffer_);
    obj.set(ReplayData::InputDataName, replay_data.simulation_actions_);
    return obj;
}

struct SimulationSystem::SimulationSystemPrivate final
{
    ReplayData current_replay_data_;
    ReplayData next_replay_data_;

    CurrentSimulationActionIterator current_simulation_action_iterator_;
    SimulateRandomDataBuffer::const_iterator
        current_simulable_data_buffer_iterator;

    time::TimePoint current_last_checked_point_;
    time::TimePoint next_last_checked_point_;

    void setSimulationActions(const time::TimePoint& current,
                              SimulationActionContainer sim_act_container)
    {
        // The passed container is now part of the data to be replayed.
        current_replay_data_.simulation_actions_.swap(sim_act_container);
        current_simulation_action_iterator_ =
            current_replay_data_.simulation_actions_.cbegin();
        current_last_checked_point_ = current;
        DisplayLog::info("Simulation System started");
    }

    void addSimulationAction(SimulationAction simulation_action)
    {
        next_replay_data_.simulation_actions_.push_back(
            std::move(simulation_action));
    }

    void setSimulateRandomDataBuffer(
        SimulateRandomDataBuffer simulated_data_buffer)
    {
        current_replay_data_.data_buffer_ = std::move(simulated_data_buffer);
        current_simulable_data_buffer_iterator =
            current_replay_data_.data_buffer_.begin();
    }
};
}  // namespace haf::sys

#endif
