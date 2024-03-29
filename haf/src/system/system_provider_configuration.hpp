HTPS_PRAGMA_ONCE
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
    htps::str window_system_configuration_file_;
};

struct HAF_PRIVATE DeserializableSystemConfigurationData
    : public data::IDeserializable
{
    static constexpr char kSimulationSystemConfigurationFile[] =
        "simulation_configuration_file";
    static constexpr char kWindowSystemConfigurationFile[] =
        "window_configuration_file";

    bool deserialize(htps::Object const& obj)
    {
        obj[kSimulationSystemConfigurationFile].as(
            data.simulation_system_configuration_file_);

        obj[kWindowSystemConfigurationFile].as(
            data.window_system_configuration_file_);

        return true;
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

    htps::str const& windowSystemConfigurationFile() const noexcept
    {
        return data().window_system_configuration_file_;
    }
};
}  // namespace haf::sys

#endif
