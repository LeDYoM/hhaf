#include <haf/system/include/interfaceaccess.hpp>
#include <haf/scene_components/include/scenemetricsview.hpp>
#include <system/i_include/get_system.hpp>
#include <scene/i_include/scenemanager.hpp>

namespace haf::sys
{
template <>
scene::ISceneMetricsView& getInterface(SystemAccess& system_access)
{
    return static_cast<scene::ISceneMetricsView&>(
        getSystem<scene::SceneManager>(&system_access));
}

template <>
scene::ISceneMetricsView const& getInterface(
    SystemAccess const& system_access)
{
    return static_cast<scene::ISceneMetricsView const&>(
        getSystem<scene::SceneManager>(&system_access));
}

}  // namespace haf::sys
