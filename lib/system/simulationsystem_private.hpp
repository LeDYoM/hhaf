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
    SimulationSystem::SimulableDataBuffer data_buffer_;
    SimulationActionContainer simulation_actions_; ///< Container containing the simulation actions to execute.

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
    CurrentSimulationActionIterator current_simulation_action_iterator_; ///< Iterator pointing to the current simulation.
    SimulableDataBuffer simulable_data_buffer_;
    SimulableDataBuffer::const_iterator current_simulable_data_buffer_iterator;
    TimePoint last_checked_point_;

    ReplayData replay_data_;

    void setSimulationActions(const TimePoint &current, SimulationActionContainer sim_act_container)
    {
        // The passed container is now part of the data to be replayed.
        replay_data_.simulation_actions_.swap(sim_act_container);
        current_simulation_action_iterator_ = replay_data_.simulation_actions_.cbegin();
        last_checked_point_ = current;
        log_debug_info("Simulation System started ");
    }

    void addSimulationAction(SimulationAction simulation_action)
    {
        replay_data_.simulation_actions_.push_back(std::move(simulation_action));
    }

    void setSimulatedDataBuffer(SimulableDataBuffer simulated_data_buffer)
    {
        simulable_data_buffer_ = std::move(simulated_data_buffer);
        current_simulable_data_buffer_iterator = simulable_data_buffer_.begin();
    }
};
} // namespace lib::core

#endif
