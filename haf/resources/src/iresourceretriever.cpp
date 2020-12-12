#include <haf/system/include/interfaceaccess.hpp>
#include <haf/resources/include/iresourceretriever.hpp>
#include <system/i_include/get_system.hpp>
#include <resources/i_include/resourcemanager.hpp>

namespace haf::sys
{
template <>
res::IResourceRetriever& getInterface(SystemAccess& system_access)
{
    return static_cast<res::IResourceRetriever&>(
        getSystem<sys::ResourceManager>(&system_access));
}

template <>
res::IResourceRetriever const& getInterface(
    SystemAccess const& system_access)
{
    return static_cast<res::IResourceRetriever const&>(
        getSystem<sys::ResourceManager>(&system_access));
}

}  // namespace haf::sys
