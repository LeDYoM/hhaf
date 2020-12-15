#include <haf/system/include/interfaceaccess.hpp>
#include <haf/resources/include/iresourceconfigurator.hpp>
#include <system/i_include/get_system.hpp>
#include <system/i_include/interfaceaccess_imp.hpp>
#include <resources/i_include/resourcemanager.hpp>

namespace haf::sys
{
GET_INTERFACE_IMP(res::IResourcesConfigurator, sys::ResourceManager)
}  // namespace haf::sys
