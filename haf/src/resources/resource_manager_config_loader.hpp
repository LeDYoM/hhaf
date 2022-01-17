#ifndef HAF_RESOURCEMANAGER_CONFIG_LOADER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_CONFIG_LOADER_INCLUDE_HPP

#include "resources_config_data.hpp"
#include <haf/include/resources/iresource_configurator.hpp>

namespace haf::sys
{
class ResourceManager;
class SubSystemViewer;
}  // namespace haf::sys

namespace haf::res
{
class ResourceManagerConfigLoader final
{
public:
    res::SetResourceConfigFileResult setResourceConfigFile(
        types::str const& config_file_name,
        sys::SubSystemViewer sub_system_viewer);
    bool loadSection(types::str const& section_name,
                     sys::ResourceManager& resource_manager);
    void setResourcesDirectory(types::str const& directory);

    htps::str const& configDirectory() const noexcept
    {
        return config_directory_;
    }

    void setConfigDirectory(htps::str const& new_value)
    {
        config_directory_ = new_value;
    }
private:
    res::SetResourceConfigFileResult parseResourceConfigFile(
        sys::SubSystemViewer sub_system_viewer);

    htps::str config_directory_{};
    htps::str resources_config_file_name_;
    res::ResourcesConfigData resources_config_data_;
};

}  // namespace haf::res

#endif
