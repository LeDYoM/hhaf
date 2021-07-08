#ifndef ZOPER_GAMEOVER_SCENENODE_INCLUDE_HPP
#define ZOPER_GAMEOVER_SCENENODE_INCLUDE_HPP

#include <haf/include/scene/transformable_scenenode.hpp>

namespace zoper
{
class GameOverSceneNode : public haf::scene::TransformableSceneNode
{
    using BaseClass = haf::scene::TransformableSceneNode;

public:
    GameOverSceneNode(haf::scene::SceneNode* const parent, htps::str name);

private:
    htps::sptr<haf::scene::TransformableSceneNode> game_over_rg_;
};
}  // namespace zoper

#endif