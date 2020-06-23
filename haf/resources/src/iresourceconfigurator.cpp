#include <haf/system/include/interfaceaccess.hpp>
#include <haf/resources/include/iresourceconfigurator.hpp>
#include <system/i_include/get_system.hpp>
#include <resources/i_include/resourcemanager.hpp>

namespace haf::sys
{
template <>
res::IResourcesConfigurator& getInterface(SystemAccess& system_access)
{
    return static_cast<res::IResourcesConfigurator&>(
        getSystem<sys::ResourceManager>(&system_access));
}

template <>
res::IResourcesConfigurator const& getInterface(
    SystemAccess const& system_access)
{
    return static_cast<res::IResourcesConfigurator const&>(
        getSystem<sys::ResourceManager>(&system_access));
}

}  // namespace haf::sys
