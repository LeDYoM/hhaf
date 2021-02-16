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
    GameHudSceneNode(mtps::rptr<haf::scene::SceneNode> const parent,
                     mtps::str name);
    ~GameHudSceneNode() override;

    void setLevel(const mtps::size_type level);
    void setStayCounter(const mtps::size_type stayCounter);
    void setConsumedTokens(const mtps::size_type consumedTokens);
    void setEllapsedTimeInSeconds(const mtps::u64 seconds);
    void setScore(const mtps::size_type score);

private:
    mtps::sptr<scene::nodes::TextQuad> m_scoreQuad;
    mtps::sptr<scene::nodes::TextQuad> m_goalQuad;
};
}  // namespace zoper

#endif