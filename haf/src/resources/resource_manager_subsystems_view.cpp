#include "system/subsystem_interface_definitions.hpp"
#include "resourcemanager.hpp"

#include <haf/include/resources/iresource_configurator.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(res::IResourceRetriever, sys::ResourceManager)
DEFINE_SUBSYSTEM_INTERFACE(res::IResourcesConfigurator, sys::ResourceManager)

}  // namespace haf::sys
