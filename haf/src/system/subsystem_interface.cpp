#include <haf/include/system/systemaccess.hpp>
#include "get_system.hpp"
#include "scene/scenemanager.hpp"
#include "render/rendersystem.hpp"
#include "resources/resourcemanager.hpp"
#include "input/inputsystem.hpp"
#include "time/timesystem.hpp"
#include "shareddata/shareddatasystem.hpp"
#include "filesystem/filesystem.hpp"

#include <haf/include/system/subsystem_interface.hpp>
#include <haf/include/resources/iresource_configurator.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

using namespace htps;

namespace haf::sys
{
#define DEFINE_SUBSYSTEM_INTERFACE(InterfaceType, SystemType)   \
template <> \
rptr<InterfaceType> subSystemInterface<InterfaceType>(  \
    rptr<SystemAccess> const system_access) \
{   \
    return &(getSystem<SystemType>(system_access));   \
}   \
    \
template <> \
rptr<InterfaceType const> subSystemInterface<InterfaceType>(    \
    rptr<SystemAccess const> const system_access)   \
{   \
    return &(getSystem<SystemType>(system_access));   \
}   \

DEFINE_SUBSYSTEM_INTERFACE(res::IResourceRetriever, sys::ResourceManager)
DEFINE_SUBSYSTEM_INTERFACE(res::IResourcesConfigurator, sys::ResourceManager)


}  // namespace haf::sys
