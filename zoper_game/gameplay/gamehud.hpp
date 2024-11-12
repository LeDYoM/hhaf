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

    haf::prop::PropertyState<htps::size_type> currentLevel;
    haf::prop::PropertyState<htps::size_type> currentScore;
    haf::prop::PropertyState<htps::size_type> currentConsumedTokens;
    haf::prop::PropertyState<htps::u64> currentEllapsedTimeInSeconds;
    haf::prop::PropertyState<htps::size_type> currentStayCounter;

    void onCreated() override;
    int foo() { return 4; }
    bool abc;
    haf::prop::PropertyState<bool> cde;

private:
    void onAllScoreElementsCreated(fmath::vector2dst const);
    void onAllGoalElementsCreated(fmath::vector2dst const);
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
