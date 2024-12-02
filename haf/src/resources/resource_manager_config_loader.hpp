HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCEMANAGER_CONFIG_LOADER_INCLUDE_HPP
#define HAF_RESOURCEMANAGER_CONFIG_LOADER_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include "resources_config_data.hpp"
#include "resource_loaders/iresource_loader.hpp"
#include <haf/include/resources/iresource_configurator.hpp>

namespace haf::sys
{
class ResourceManager;
class SubSystemViewer;
}  // namespace haf::sys

namespace haf::res
{
class HAF_PRIVATE ResourceManagerConfigLoader final
{
public:
    res::SetResourceConfigFileResult setResourceConfigFile(
        htps::str const& config_file_name,
        sys::SubSystemViewer sub_system_viewer);
    bool loadSection(htps::str const& section_name,
                     IResourceLoader& resource_loader);
    void setResourcesDirectory(htps::str const& directory);

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
