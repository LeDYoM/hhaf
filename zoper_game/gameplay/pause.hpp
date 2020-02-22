#pragma once

#ifndef ZOOPER_GAME_PAUSE_INCLUDE_HPP
#define ZOOPER_GAME_PAUSE_INCLUDE_HPP

#include <mtypes/include/types.hpp>

#include <lib/scene/include/scenenode.hpp>
#include <lib/scene_nodes/include/scenenodetext.hpp>
#include <lib/scene_components/include/animationcomponent.hpp>

#include "../gameshareddata.hpp"

namespace zoper
{
class GameScene;

using namespace lib;

class PauseSceneNode : public scene::SceneNode
{
public:
    PauseSceneNode(scene::SceneNode *const parent, str name);
    ~PauseSceneNode() override;

    void enterPause();
    void exitPause();

private:
    sptr<scene::nodes::SceneNodeText> m_pauseText;
    sptr<scene::AnimationComponent> animation_component_;
};
} // namespace zoper

#endif
