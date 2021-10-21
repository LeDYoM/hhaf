#include <haf/include/system/isystemprovider.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/system/systemaccess.hpp>
#include "get_systemprovider.hpp"
#include "systemprovider.hpp"
#include "get_system.hpp"
#include "scene/scenemanager.hpp"
#include "render/rendersystem.hpp"
#include "resources/resourcemanager.hpp"
#include "input/inputsystem.hpp"
#include "time/timesystem.hpp"
#include "shareddata/shareddatasystem.hpp"
#include "filesystem/filesystem.hpp"

using namespace htps;

namespace haf::sys
{
#define DEFINE_GETSYSTEM(SystemType, callFunction) \
    template <> \
    const SystemType& getSystem<SystemType>( \
        rptr<const SystemAccess> system_access) \
    { \
        return getSystemProvider(system_access->isystemProvider()) \
            .callFunction(); \
    } \
\
    template <> \
    SystemType& getSystem<SystemType>(rptr<SystemAccess> system_access) \
    { \
        return getSystemProvider(system_access->isystemProvider()) \
            .callFunction(); \
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

DEFINE_GETSYSTEM(sys::InputSystem, inputSystem)
DEFINE_GETSYSTEM(scene::SceneManager, sceneManager)
DEFINE_GETSYSTEM(sys::RenderSystem, renderSystem)
DEFINE_GETSYSTEM(sys::ResourceManager, resourceManager)
DEFINE_GETSYSTEM(sys::TimeSystem, timeSystem)
DEFINE_GETSYSTEM(sys::SharedDataSystem, sharedDataSystem)
DEFINE_GETSYSTEM(sys::RandomSystem, randomSystem)
DEFINE_GETSYSTEM(sys::FileSystem, fileSystem)
}  // namespace haf::sys
