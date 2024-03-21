HAF_PRAGMA_ONCE
#ifndef HAF_SYSTEM_SYSTEM_PROVIDER_CONFIGURATION_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_PROVIDER_CONFIGURATION_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>
#include <haf/include/data/types.hpp>
#include "system/system_configuration.hpp"

namespace haf::sys
{
struct SystemConfigurationData
{
    core::str simulation_system_configuration_file_;
    core::str window_system_configuration_file_;
};

struct DeserializableSystemConfigurationData final
    : public data::IDeserializable
{
    static constexpr char kSimulationSystemConfigurationFile[] =
        "simulation_configuration_file";
    static constexpr char kWindowSystemConfigurationFile[] =
        "window_configuration_file";

    bool deserialize(mcs::Object const& obj)
    {
        obj[kSimulationSystemConfigurationFile].as(
            data.simulation_system_configuration_file_);

        obj[kWindowSystemConfigurationFile].as(
            data.window_system_configuration_file_);

        return true;
    }

    SystemConfigurationData data;
};

class SystemProviderConfiguration final
    : public SystemConfiguration<DeserializableSystemConfigurationData,
                                 SystemConfigurationData>
{
public:
    core::str const& simulationSystemConfigurationFile() const noexcept
    {
        return data().simulation_system_configuration_file_;
    }

    core::str const& windowSystemConfigurationFile() const noexcept
    {
        return data().window_system_configuration_file_;
    }
};
}  // namespace haf::sys

#endif
