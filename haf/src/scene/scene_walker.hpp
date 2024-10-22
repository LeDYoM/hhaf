HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_WALKER_INCLUDE_HPP
#define HAF_SCENE_SCENE_WALKER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "haf_private.hpp"
#include <haf/include/scene/scene_render_context.hpp>

namespace haf::scene
{
class SceneNode;
class Scene;
}

namespace haf
{
    class ISceneSubsystem
    {
        virtual bool onPassStart() = 0;
        virtual bool onScenePass(scene::Scene&) = 0;
        virtual bool onSceneNodePass(scene::SceneNode&) = 0;
        virtual bool onSceneTreeDown() = 0;
        virtual bool onSceneTreeUp() = 0;
        virtual bool onPassFinished() = 0;
        virtual ~ISceneSubsystem() = default;
    };
}

namespace haf::scene
{

void HAF_PRIVATE walk(Scene& scene_node, ISceneSubsystem& iscene_subsystem);
void HAF_PRIVATE walk(SceneNode& scene_node, ISceneSubsystem& iscene_subsystem);

}  // namespace haf::scene

#endif
