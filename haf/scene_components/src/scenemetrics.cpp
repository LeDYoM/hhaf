#include <haf/system/include/interfaceaccess.hpp>
#include <haf/scene_components/include/scenemetrics.hpp>
#include <system/i_include/get_system.hpp>
#include <scene/i_include/scenemanager.hpp>

namespace haf::sys
{
template <>
scene::ISceneMetrics& getInterface(SystemAccess& system_access)
{
    return static_cast<scene::ISceneMetrics&>(
        getSystem<scene::SceneManager>(&system_access));
}

template <>
scene::ISceneMetrics const& getInterface(
    SystemAccess const& system_access)
{
    return static_cast<scene::ISceneMetrics const&>(
        getSystem<scene::SceneManager>(&system_access));
}

}  // namespace haf::sys
