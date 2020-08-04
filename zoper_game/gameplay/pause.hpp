#pragma once

#ifndef ZOOPER_GAME_PAUSE_INCLUDE_HPP
#define ZOOPER_GAME_PAUSE_INCLUDE_HPP

#include <mtypes/include/types.hpp>

#include <haf/scene/include/scenenode.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>
#include <haf/scene_components/include/animationcomponent.hpp>

#include "../gameshareddata.hpp"

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
    mtps::sptr<haf::scene::nodes::SceneNodeText> m_pauseText;
    mtps::sptr<haf::scene::AnimationComponent> animation_component_;
};
} // namespace zoper

#endif
