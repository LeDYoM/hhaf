HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_WALKER_INCLUDE_HPP
#define HAF_SCENE_SCENE_WALKER_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::scene
{
class SceneNode;
class ISceneManagerSubSystem;
class SceneManagerSubSystemGroup;

}  // namespace haf::scene

namespace haf::scene
{
class SceneWalker final
{
public:
    void startWalk(SceneNode& rootNode, SceneManagerSubSystemGroup& sceneManagerSubSystemGroup);
    void walk(SceneNode& node, ISceneManagerSubSystem& iSceneManagerSubSystem);
};

}  // namespace haf::scene

#endif
