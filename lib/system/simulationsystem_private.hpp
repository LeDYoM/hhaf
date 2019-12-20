#pragma once

#ifndef LIB_CORE_SYSTEM_SIMULATIONSYSTEM_PRIVATE_INCLUDE_HPP
#define LIB_CORE_SYSTEM_SIMULATIONSYSTEM_PRIVATE_INCLUDE_HPP

#include "simulationsystem.hpp"
#include "simulationaction.hpp"

#include "timesystem.hpp"
#include "inputsystem.hpp"

#include <lib/include/key.hpp>
#include <lib/include/liblog.hpp>
#include <lib/include/core/timepoint.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/system/simulationsystem.hpp>
#include <lib/system/randomsystem.hpp>

#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/object_utils.hpp>

namespace lib::core
{

struct ReplayData
{
    SimulationSystem::SimulateRandomDataBuffer data_buffer_;
    SimulationActionContainer simulation_actions_;

    constexpr static char DataBufferName[] = "replay_data";
    constexpr static char InputDataName[] = "input_data";
};

const Object &operator>>(const Object &obj, ReplayData &replay_data)
{
    if (const auto obj_random_generator_data = obj[ReplayData::DataBufferName]; obj_random_generator_data.isObject())
    {
        obj_random_generator_data.getObject() >> replay_data.data_buffer_;
    }

    if (const auto obj_input_data = obj[ReplayData::InputDataName]; obj_input_data.isObject())
    {
        obj_input_data.getObject() >> replay_data.simulation_actions_;
    }

    return obj;
}

inline Object &operator<<(Object &obj, const ReplayData &replay_data)
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
    SimulateRandomDataBuffer::const_iterator current_simulable_data_buffer_iterator;

    TimePoint current_last_checked_point_;
    TimePoint next_last_checked_point_;

    void setSimulationActions(const TimePoint &current, SimulationActionContainer sim_act_container)
    {
        // The passed container is now part of the data to be replayed.
        current_replay_data_.simulation_actions_.swap(sim_act_container);
        current_simulation_action_iterator_ = current_replay_data_.simulation_actions_.cbegin();
        current_last_checked_point_ = current;
        DisplayLog::info("Simulation System started");
    }

    void addSimulationAction(SimulationAction simulation_action)
    {
        next_replay_data_.simulation_actions_.push_back(std::move(simulation_action));
    }

    void setSimulateRandomDataBuffer(SimulateRandomDataBuffer simulated_data_buffer)
    {
        current_replay_data_.data_buffer_ = std::move(simulated_data_buffer);
        current_simulable_data_buffer_iterator = current_replay_data_.data_buffer_.begin();
    }
};
} // namespace lib::core

#endif
