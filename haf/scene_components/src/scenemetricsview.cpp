#include <haf/system/include/interfaceaccess.hpp>
#include <haf/scene_components/include/scenemetricsview.hpp>
#include <system/i_include/get_system.hpp>
#include <system/i_include/interfaceaccess_imp.hpp>
#include <scene/i_include/scenemanager.hpp>

namespace haf::sys
{
GET_INTERFACE_IMP(scene::ISceneMetricsView, scene::SceneManager)
}  // namespace haf::sys
