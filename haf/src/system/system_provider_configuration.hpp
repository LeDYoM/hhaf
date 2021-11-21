#ifndef HAF_SYSTEM_SYSTEM_PROVIDER_CONFIGURATION_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_PROVIDER_CONFIGURATION_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/data/ideserializable.hpp>
#include "system/system_configuration.hpp"

namespace haf::sys
{
struct HAF_PRIVATE SystemConfigurationData
{
    htps::str simulation_system_configuration_file_;
};

struct HAF_PRIVATE DeserializableSystemConfigurationData
    : public data::IDeserializable
{
    static constexpr char kSimulationSystemFile[] =
        "simulation_configuration.txt";

    bool deserialize(htps::Object const& obj)
    {
        bool result{true};
        result &= obj[kSimulationSystemFile].as(
            data.simulation_system_configuration_file_);

        return result;
    }

    SystemConfigurationData data;
};

class HAF_PRIVATE SystemProviderConfiguration
    : public SystemConfiguration<DeserializableSystemConfigurationData,
                                 SystemConfigurationData>
{
public:
    htps::str const& simulationSystemConfigurationFile() const noexcept
    {
        return data().simulation_system_configuration_file_;
    }
};
}  // namespace haf::sys

#endif
