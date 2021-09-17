#include "gamescene_private.hpp"
#include "constants.hpp"
#include <htypes/include/types.hpp>

#include <haf/include/animation/animation_component.hpp>
#include <haf/include/random/randomnumberscomponent.hpp>
#include <haf/include/render/fig_type.hpp>

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
    auto pointsToScoreSceneNode =
        main_node.createSceneNode<RenderizablesSceneNode>(
            "pointIncrementScore_SceneNode");

    auto node = pointsToScoreSceneNode->renderizableBuilder()
                    .name("pointIncrementScore")
                    .figType(FigType_t::Shape)
                    .box(rectFromSize(15.0F, 15.0F))
                    .color(colors::White)
                    .pointCount(30U)
                    .create();

    {
        using namespace gameplay::constants;

        DisplayLog::info("Creating animation for points to score");
        auto property_animation_builder =
            scene_animation_component_
                ->make_property_animation_builder<Position>(
                    pointsToScoreSceneNode);
        property_animation_builder->startValue(lastTokenPosition)
            .endValue(EndPositionPointsToScore)
            .duration(
                time::TimePoint_as_miliseconds(MillisAnimationPointsToScore))
            .endAction([pointsToScoreSceneNode]() {
                pointsToScoreSceneNode->autoRemove();
            });

        scene_animation_component_->addAnimation(
            std::move(property_animation_builder));
    }
}
}  // namespace zoper
