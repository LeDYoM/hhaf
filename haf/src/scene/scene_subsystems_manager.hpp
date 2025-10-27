HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_SUBSYSTEMS_MANAGER_INCLUDE_HPP
#define HAF_SCENE_SCENE_SUBSYSTEMS_MANAGER_INCLUDE_HPP

#include "haf_private.hpp"
#include <haf/include/core/types.hpp>

#include "scene_subsystems.hpp"

namespace haf::scene
{
class SceneNode;
class HAF_PRIVATE SceneSubsystemsManager final
{
public:
    void addSceneSubsystem(SceneSubsystem&& scene_subsystem);
    void processAllOrderedComponents(SceneNode& scene_node);
    void processAllUnorderedComponents(SceneNode& scene_node);

private:
    SceneSubsystems m_scene_subsystems;
};

}  // namespace haf::scene

#endif
