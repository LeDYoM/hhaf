#include "get_systemprovider.hpp"
#include "systemprovider.hpp"
#include "isystemprovider.hpp"
#include "get_system.hpp"
#include <haf/scene/include/scenenode.hpp>
#include "systemaccess.hpp"
#include <scene/i_include/scenemanager.hpp>
#include <render/i_include/rendersystem.hpp>
#include <resources/i_include/resourcemanager.hpp>
#include <input/i_include/inputsystem.hpp>
#include <time/i_include/timesystem.hpp>
#include <shareddata/i_include/shareddatasystem.hpp>
#include <filesystem/i_include/filesystem.hpp>

using namespace mtps;

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
    const SystemType& getSystem<SystemType>( \
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

DEFINE_GETSYSTEM(sys::InputSystem, inputSystem);
DEFINE_GETSYSTEM(scene::SceneManager, sceneManager);
DEFINE_GETSYSTEM(sys::RenderSystem, renderSystem);
DEFINE_GETSYSTEM(sys::ResourceManager, resourceManager);
DEFINE_GETSYSTEM(sys::TimeSystem, timeSystem);
DEFINE_GETSYSTEM(sys::SharedDataSystem, sharedDataSystem);
DEFINE_GETSYSTEM(sys::RandomSystem, randomSystem);
DEFINE_GETSYSTEM(sys::FileSystem, fileSystem);
}  // namespace haf::sys
