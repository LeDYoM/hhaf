#ifndef ZOPER_GAMEHUD_SCENENODE_INCLUDE_HPP
#define ZOPER_GAMEHUD_SCENENODE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/scene_nodes/scene_node_text_quad.hpp>

namespace zoper
{

class GameHudSceneNode final : public haf::scene::TransformableSceneNode
{
    using BaseClass = haf::scene::TransformableSceneNode;

public:
    using BaseClass::BaseClass;

    void update() override;

    htps::PropertyState<htps::size_type> currentLevel;
    void onCreated() override;
    void setStayCounter(const htps::size_type stayCounter);
    void setConsumedTokens(const htps::size_type consumedTokens);
    void setEllapsedTimeInSeconds(const htps::u64 seconds);
    void setScore(const htps::size_type score);

private:
    void onAllScoreElementsCreated();
    void onAllGoalElementsCreated();
    bool setLevel(const htps::size_type level);

    htps::sptr<haf::scene::nodes::TextQuad> score_quad_;
    htps::sptr<haf::scene::nodes::TextQuad> goal_quad_;
};
}  // namespace zoper

#endif