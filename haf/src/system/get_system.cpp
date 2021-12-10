#include <haf/include/system/isystemprovider.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/system/systemaccess.hpp>
#include "get_systemprovider.hpp"
#include "systemprovider.hpp"
#include "get_system.hpp"
#include "scene/scene_manager.hpp"
#include "render/rendersystem.hpp"
#include "resources/resourcemanager.hpp"
#include "input/inputsystem.hpp"
#include "time/timesystem.hpp"
#include "shareddata/shareddatasystem.hpp"
#include "filesystem/file_system.hpp"
#include "debug_utils/debug_system.hpp"

using namespace htps;

namespace haf::sys
{
#define DEFINE_GETSYSTEM(SystemType) \
    template <> \
    const SystemType& getSystem<SystemType>( \
        rptr<const SystemAccess> system_access) \
    { \
        return getSystemProvider(system_access->isystemProvider()) \
            .system<SystemType>(); \
    } \
\
    template <> \
    SystemType& getSystem<SystemType>(rptr<SystemAccess> system_access) \
    { \
        return getSystemProvider(system_access->isystemProvider()) \
            .system<SystemType>(); \
    } \
\
    template <> \
    const SystemType& getSystem<SystemType>( \
        rptr<ISystemProvider const> isystem_provider) \
    { \
        return getSystemProvider(*isystem_provider) \
            .system<SystemType>(); \
    } \
\
    template <> \
    SystemType& getSystem<SystemType>(rptr<ISystemProvider> isystem_provider) \
    { \
        return getSystemProvider(*isystem_provider) \
            .system<SystemType>(); \
    } \
\
    template <> \
    SystemType const& getSystem<SystemType>( \
        rptr<const scene::SceneNode> scene_node) \
    { \
        return getSystem<SystemType>( \
            static_cast<rptr<const SystemAccess>>(scene_node)); \
    } \
\
    template <> \
    SystemType& getSystem<SystemType>(rptr<scene::SceneNode> scene_node) \
    { \
        return getSystem<SystemType>( \
            static_cast<rptr<SystemAccess>>(scene_node)); \
    }

DEFINE_GETSYSTEM(sys::DebugSystem)
DEFINE_GETSYSTEM(sys::InputSystem)
DEFINE_GETSYSTEM(scene::SceneManager)
DEFINE_GETSYSTEM(sys::RenderSystem)
DEFINE_GETSYSTEM(sys::ResourceManager)
DEFINE_GETSYSTEM(sys::TimeSystem)
DEFINE_GETSYSTEM(sys::SharedDataSystem)
DEFINE_GETSYSTEM(sys::RandomSystem)
DEFINE_GETSYSTEM(sys::FileSystem)
}  // namespace haf::sys
