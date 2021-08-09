#ifndef ZOOPER_GAME_PAUSE_INCLUDE_HPP
#define ZOOPER_GAME_PAUSE_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>
#include <haf/include/animation/animationcomponent.hpp>

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
    htps::sptr<haf::scene::nodes::SceneNodeText> m_pauseText;
    htps::sptr<haf::anim::AnimationComponent> animation_component_;
};
}  // namespace zoper

#endif
