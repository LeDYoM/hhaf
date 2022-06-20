#ifndef ZOOPER_GAME_PAUSE_INCLUDE_HPP
#define ZOOPER_GAME_PAUSE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <haf/include/animation/animation_component.hpp>

namespace zoper
{
class GameScene;

class PauseSceneNode : public haf::scene::SceneNode
{
public:
    using haf::scene::SceneNode::SceneNode;

    ~PauseSceneNode() override;

    void onCreated() override;

    void enterPause();
    void exitPause();

private:
    htps::sptr<haf::scene::nodes::SceneNodeText> pause_text_;
    htps::sptr<haf::anim::AnimationComponent> animation_component_;
};
}  // namespace zoper

#endif
