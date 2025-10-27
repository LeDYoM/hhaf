#include "scene_subsystems_manager.hpp"

#include <haf/include/core/log.hpp>
#include <haf/include/scene/scene_node.hpp>
#include "scene_render.hpp"


using namespace haf::core;

namespace haf::scene
{
void SceneSubsystemsManager::addSceneSubsystem(SceneSubsystem&& scene_subsystem)
{
    m_scene_subsystems.addSceneSubsystem(core::move(scene_subsystem));
}

void SceneSubsystemsManager::processAllOrderedComponents(SceneNode& scene_node)
{
    for (auto&& scene_subsystem : m_scene_subsystems)
    {
        processOrderedComponents(scene_node, scene_subsystem.index());
    }
}

void SceneSubsystemsManager::processAllUnorderedComponents(SceneNode& scene_node)
{
    processUnorderedComponents(scene_node);
}

}  // namespace haf::scene
