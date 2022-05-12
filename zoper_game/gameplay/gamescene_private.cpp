#include "gamescene_private.hpp"
#include "constants.hpp"
#include <htypes/include/types.hpp>

#include <haf/include/animation/animation_component.hpp>
#include <haf/include/random/randomnumberscomponent.hpp>
#include <haf/include/render/fig_type.hpp>
#include <haf/include/scene_components/camera_component.hpp>

using namespace haf::scene;
using namespace haf::render;
using namespace haf::anim;

using namespace htps;

namespace zoper
{
void GameScene::GameScenePrivate::createScoreIncrementPoints(
    SceneNode& main_node,
    vector2df const& lastTokenPosition)
{
    auto pointsToScoreSceneNode{
        main_node.createSceneNode<RenderizableSceneNode>(
            "pointIncrementScore_SceneNode")};

    auto node{pointsToScoreSceneNode->renderizableBuilder()
                    .name("pointIncrementScore")
                    .figType(FigType_t::Sprite)
                    .color(colors::White)
//                    .pointCount(30U)
                    .create()};

    pointsToScoreSceneNode->prop<Scale>() = vector2df{0.01F, 0.01F};
    using namespace gameplay::constants;

    DisplayLog::info("Creating animation for points to score");

    auto property_animation_builder{
        scene_animation_component_->make_property_animation_builder<Position>(
            pointsToScoreSceneNode)};
    property_animation_builder.startValue(lastTokenPosition)
        .endValue(EndPositionPointsToScore)
        .duration(time::TimePoint_as_miliseconds(MillisAnimationPointsToScore))
        .actionWhenFinished([pointsToScoreSceneNode]() {
            pointsToScoreSceneNode->autoRemove();
        });

    pointsToScoreSceneNode->prop<Position>() = EndPositionPointsToScore;

    scene_animation_component_->addAnimation(
        htps::move(property_animation_builder));
}
}  // namespace zoper
