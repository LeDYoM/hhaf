HAF_PRAGMA_ONCE
#ifndef HAF_SIMULATION_SIMULATION_CONFIGURATION_INCLUDE_HPP
#define HAF_SIMULATION_SIMULATION_CONFIGURATION_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/data/ideserializable.hpp>
#include "system/system_configuration.hpp"

namespace haf::sys
{
struct HAF_PRIVATE SimulationData
{
    bool global_use;
    htps::str simulation_input_file;
    htps::str simulation_output_file;
    htps::f32 speed;
};

struct HAF_PRIVATE DeserializableSimulationData : public data::IDeserializable
{
    static constexpr char SimulationInputFileStr[] = "read_input";
    static constexpr char SimulationOutputFile[]   = "write_output";

    bool deserialize(mcs::Object const& obj)
    {
        data.global_use |=
            obj[SimulationInputFileStr].as(data.simulation_input_file);
        data.global_use |=
            obj[SimulationOutputFile].as(data.simulation_output_file);

        return true;
    }

    SimulationData data;
};

class SimulationSystemConfiguration
    : public SystemConfiguration<DeserializableSimulationData, SimulationData>
{
public:
    bool globalUse() const noexcept { return data().global_use; }

    htps::str const& simulationInputFileName() const noexcept
    {
        return data().simulation_input_file;
    }

    htps::str const& simulationOutputFileName() const noexcept
    {
        return data().simulation_output_file;
    }

    bool useInputSimulation() const noexcept
    {
        return !data().simulation_input_file.empty() && data().global_use;
    }

    bool useOutputSimulation() const noexcept
    {
        return !data().simulation_output_file.empty() && data().global_use;
    }
};
}  // namespace haf::sys

#endif
