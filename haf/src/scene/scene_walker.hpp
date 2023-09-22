HAF_PRAGMA_ONCE
#ifndef HAF_SCENE_SCENE_WALKER_INCLUDE_HPP
#define HAF_SCENE_SCENE_WALKER_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::scene
{
class SceneNode;
enum class SceneUpdateTime : core::u32;
}  // namespace haf::scene

namespace haf::scene
{
class SceneWalker final
{
public:
    void startWalk(SceneNode& rootNode);
    void walk(SceneNode& node);
    void walk(SceneNode& node, SceneUpdateTime const sceneUpdateTime);
};

}  // namespace haf::scene

#endif
