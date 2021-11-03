#ifndef HAF_RESOURCEMANAGER_CONFIG_LOADER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_CONFIG_LOADER_INCLUDE_HPP

#include "resources_config_data.hpp"
#include <haf/include/resources/iresource_configurator.hpp>

namespace haf::res
{
class ResourceManagerConfigLoader final
{
public:
    res::SetResourceConfigFileResult setResourceConfigFile(
        types::str const& config_file_name);
    bool loadSection(types::str const& section_name);
    void setResourcesDirectory(types::str const& directory);

    res::SetResourceConfigFileResult parseResourceConfigFile();

private:
    htps::str resources_config_file_name_;
    res::ResourcesConfigData resources_config_data_;
};

}  // namespace haf::sys

#endif
