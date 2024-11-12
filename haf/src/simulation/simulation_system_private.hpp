HTPS_PRAGMA_ONCE
#ifndef HAF_CORE_SYSTEM_SIMULATIONSYSTEM_PRIVATE_INCLUDE_HPP
#define HAF_CORE_SYSTEM_SIMULATIONSYSTEM_PRIVATE_INCLUDE_HPP

#include "simulation_system.hpp"
#include <haf/include/simulation/simulationaction.hpp>

#include <haf/include/input/key.hpp>
#include <haf/include/time/time_point.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <hlog/include/hlog.hpp>
#include "system/system_provider.hpp"
#include "random/randomsystem.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <facil_math/include/rect.hpp>
#include <mc_serial/include/object.hpp>

namespace haf::sys
{

struct ReplayData : public data::IFullSerializable
{
    SimulationSystem::SimulateRandomDataBuffer data_buffer_;
    SimulationActionContainer simulation_actions_;

    constexpr static char DataBufferName[] = "replay_data";
    constexpr static char InputDataName[]  = "input_data";

    friend const mcs::Object& operator>>(const mcs::Object& obj,
                                          ReplayData& replay_data);
    friend mcs::Object& operator<<(mcs::Object& obj,
                                    const ReplayData& replay_data);

    bool serialize(mcs::Object& obj) const override
    {
        obj << *this;
        return true;
    }

    bool deserialize(mcs::Object const& obj) override
    {
        obj >> *this;
        return true;
    }

    ~ReplayData() override = default;
};

const mcs::Object& operator>>(const mcs::Object& obj, ReplayData& replay_data)
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

mcs::Object& operator<<(mcs::Object& obj, const ReplayData& replay_data)
{
    obj.set(ReplayData::DataBufferName, replay_data.data_buffer_);
    obj.set(ReplayData::InputDataName, replay_data.simulation_actions_);
    return obj;
}

struct SimulationSystem::SimulationSystemPrivate final
{
    ReplayData current_replay_data_;
    ReplayData next_replay_data_;

    CurrentSimulationActionIterator current_simulation_action_iterator_{};
    SimulateRandomDataBuffer::const_iterator
        current_simulable_data_buffer_iterator{};

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
            htps::move(simulation_action));
    }

    void setSimulateRandomDataBuffer(
        SimulateRandomDataBuffer simulated_data_buffer)
    {
        current_replay_data_.data_buffer_ = htps::move(simulated_data_buffer);
        current_simulable_data_buffer_iterator =
            current_replay_data_.data_buffer_.begin();
    }
};
}  // namespace haf::sys

#endif
