#include "system/subsystem_interface_definitions.hpp"
#include "scene/scene_manager.hpp"

#include <haf/include/scene_components/scenemetricsview.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(scene::ISceneMetricsView, scene::SceneManager)

}  // namespace haf::sys
