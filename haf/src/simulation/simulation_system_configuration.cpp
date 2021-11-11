#include "simulation_system_configuration.hpp"

#include <haf/include/filesystem/fileserializer.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace htps;

namespace haf::sys
{

struct HAF_PRIVATE DeserializableSimulationData : public data::IDeserializable
{
    static constexpr char SimulationInputFileStr[]   = "read_input";
    static constexpr char SimulationOutputFile[] = "write_output";

    bool deserialize(htps::Object const& obj)
    {
        data.global_use |= obj[SimulationInputFileStr].as(data.simulation_input_file);
        data.global_use |= obj[SimulationOutputFile].as(data.simulation_output_file);
        return true;
    }

    SimulationData data;
};

void SimulationSystemConfiguration::loadConfiguration(
    DataWrapperCreator& data_wrapper_creator,
    str const& configuration_file_name)
{
    DeserializableSimulationData current;
    auto file_serializer{
        data_wrapper_creator.dataWrapper<sys::FileSerializer>()};
    auto const result{
        file_serializer->deserializeFromFile(configuration_file_name, current)};
}

}  // namespace haf::sys
