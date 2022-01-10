#ifndef ZOPER_GAMEHUD_SCENENODE_INCLUDE_HPP
#define ZOPER_GAMEHUD_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/transformable_scene_node.hpp>
#include <haf/include/scene_nodes/scene_node_text_quad.hpp>

namespace zoper
{

class GameHudSceneNode final : public haf::scene::TransformableSceneNode
{
    using BaseClass = haf::scene::TransformableSceneNode;

public:
    GameHudSceneNode(htps::rptr<haf::scene::SceneNode> const parent,
                     htps::str name);

    void setLevel(const htps::size_type level);
    void setStayCounter(const htps::size_type stayCounter);
    void setConsumedTokens(const htps::size_type consumedTokens);
    void setEllapsedTimeInSeconds(const htps::u64 seconds);
    void setScore(const htps::size_type score);

private:
    htps::sptr<haf::scene::nodes::TextQuad> score_quad_;
    htps::sptr<haf::scene::nodes::TextQuad> goal_quad_;
};
}  // namespace zoper

#endif