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
    htps::PropertyState<htps::size_type> currentScore;
    htps::PropertyState<htps::size_type> currentConsumedTokens;
    htps::PropertyState<htps::u64> currentEllapsedTimeInSeconds;
    htps::PropertyState<htps::size_type> currentStayCounter;

    void onCreated() override;

private:
    void onAllScoreElementsCreated();
    void onAllGoalElementsCreated();
    bool setLevel(const htps::size_type level);
    bool setScore(htps::size_type const score);
    bool setConsumedTokens(htps::size_type const consumedTokens);
    bool setEllapsedTimeInSeconds(htps::u64 const seconds);
    bool setStayCounter(htps::size_type const stayCounter);

    htps::sptr<haf::scene::nodes::TextQuad> score_quad_;
    htps::sptr<haf::scene::nodes::TextQuad> goal_quad_;
};
}  // namespace zoper

#endif