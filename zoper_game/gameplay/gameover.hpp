#ifndef ZOPER_GAMEOVER_SCENENODE_INCLUDE_HPP
#define ZOPER_GAMEOVER_SCENENODE_INCLUDE_HPP

#include <haf/include/scene_nodes/transformable_scene_node.hpp>

namespace zoper
{
class GameOverSceneNode : public haf::scene::TransformableSceneNode
{
    using BaseClass = haf::scene::TransformableSceneNode;

public:
    using BaseClass::BaseClass;

    void onCreated() override;

private:
    htps::sptr<haf::scene::TransformableSceneNode> game_over_rg_;
};
}  // namespace zoper

#endif