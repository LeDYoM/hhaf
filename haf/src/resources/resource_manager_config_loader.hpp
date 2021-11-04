#ifndef HAF_RESOURCEMANAGER_CONFIG_LOADER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_CONFIG_LOADER_INCLUDE_HPP

#include "resources_config_data.hpp"
#include <haf/include/resources/iresource_configurator.hpp>

namespace haf::sys
{
class DataWrapperCreator;
class ResourceManager;
}  // namespace haf::sys

namespace haf::res
{
class ResourceManagerConfigLoader final
{
public:
    res::SetResourceConfigFileResult setResourceConfigFile(
        types::str const& config_file_name,
        sys::DataWrapperCreator& data_wrapper_creator);
    bool loadSection(types::str const& section_name,
                     sys::ResourceManager& resource_manager);
    void setResourcesDirectory(types::str const& directory);

    res::SetResourceConfigFileResult parseResourceConfigFile(
        sys::DataWrapperCreator& data_wrapper_creator);

    htps::str config_directory_{};
    htps::str resources_config_file_name_;
    res::ResourcesConfigData resources_config_data_;
};

}  // namespace haf::res

#endif
