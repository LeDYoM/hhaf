#include "system/subsystem_interface_definitions.hpp"
#include "resource_manager.hpp"

#include <haf/include/resources/iresource_configurator.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(res::IResourceRetriever, sys::ResourceManager)
DEFINE_SUBSYSTEM_INTERFACE(res::IResourcesConfigurator, sys::ResourceManager)

}  // namespace haf::sys
