#ifndef ZOPER_GAMEHUD_SCENENODE_INCLUDE_HPP
#define ZOPER_GAMEHUD_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <haf/scene_nodes/include/textquad.hpp>

namespace zoper
{
using namespace haf;

class GameHudSceneNode : public scene::SceneNode
{
public:
    GameHudSceneNode(htps::rptr<haf::scene::SceneNode> const parent,
                     htps::str name);
    ~GameHudSceneNode() override;

    void setLevel(const htps::size_type level);
    void setStayCounter(const htps::size_type stayCounter);
    void setConsumedTokens(const htps::size_type consumedTokens);
    void setEllapsedTimeInSeconds(const htps::u64 seconds);
    void setScore(const htps::size_type score);

private:
    htps::sptr<scene::nodes::TextQuad> m_scoreQuad;
    htps::sptr<scene::nodes::TextQuad> m_goalQuad;
};
}  // namespace zoper

#endif