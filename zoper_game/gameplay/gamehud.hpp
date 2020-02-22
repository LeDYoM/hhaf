#pragma once

#ifndef ZOPER_GAMEHUD_SCENENODE_INCLUDE_HPP
#define ZOPER_GAMEHUD_SCENENODE_INCLUDE_HPP

#include <lib/scene/scenenode.hpp>
#include <lib/scene_nodes/include/textquad.hpp>

namespace zoper
{
using namespace lib;

class GameHudSceneNode : public scene::SceneNode
{
public:
    GameHudSceneNode(scene::SceneNode *const parent, str name);
    ~GameHudSceneNode() override;

    void setLevel(const size_type level);
    void setStayCounter(const size_type stayCounter);
    void setConsumedTokens(const size_type consumedTokens);
    void setEllapsedTimeInSeconds(const u64 seconds);
    void setScore(const size_type score);

private:
    sptr<scene::nodes::TextQuad> m_scoreQuad;
    sptr<scene::nodes::TextQuad> m_goalQuad;
};
} // namespace zoper

#endif