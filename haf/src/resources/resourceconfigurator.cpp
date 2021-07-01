#include <haf/include/resources/resourceconfigurator.hpp>
#include "resourcemanager.hpp"

#include "system/get_system.hpp"

namespace haf::res
{
void ResourcesConfigurator::setResourcesDirectory(htps::str directory)
{
    return sys::getSystem<sys::ResourceManager>(attachedNode())
        .setResourcesDirectory(std::move(directory));
}

SetResourceConfigFileResult ResourcesConfigurator::setResourceConfigFile(
    htps::str fileName)
{
    return sys::getSystem<sys::ResourceManager>(attachedNode())
        .setResourceConfigFile(std::move(fileName));
}

bool ResourcesConfigurator::loadSection(htps::str const& section)
{
    return sys::getSystem<sys::ResourceManager>(attachedNode())
        .loadSection(section);
}

}  // namespace haf::res
