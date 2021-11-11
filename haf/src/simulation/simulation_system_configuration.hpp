#ifndef HAF_SIMULATION_SIMULATION_CONFIGURATION_INCLUDE_HPP
#define HAF_SIMULATION_SIMULATION_CONFIGURATION_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/data/ideserializable.hpp>

namespace haf::sys
{
class DataWrapperCreator;

struct HAF_PRIVATE SimulationData
{
    bool global_use;
    htps::str simulation_input_file;
    htps::str simulation_output_file;
    htps::f32 speed;
};

class HAF_PRIVATE SimulationSystemConfiguration
{
public:
    void loadConfiguration(DataWrapperCreator& data_wrapper_creator,
                           htps::str const& simulation_config_file);

    SimulationData const& simulationData() const noexcept
    {
        return simulation_data_;
    }

private:
    SimulationData simulation_data_;
};
}  // namespace haf::sys

#endif
