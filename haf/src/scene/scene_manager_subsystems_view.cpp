#include "system/subsystem_interface_definitions.hpp"
#include "scene/scene_manager.hpp"

#include <haf/include/scene_components/iscene_control.hpp>
#include <haf/include/scene_components/iapp_initializer.hpp>
#include <haf/include/scene_components/iapp_finisher.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(scene::ISceneControl, scene::SceneManager)
DEFINE_SUBSYSTEM_INTERFACE(scene::IAppInitializer, scene::SceneManager)
DEFINE_SUBSYSTEM_INTERFACE(scene::IAppFinisher, scene::SceneManager)
}  // namespace haf::sys
