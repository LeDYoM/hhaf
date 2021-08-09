#include "gamescene_private.hpp"
#include "constants.hpp"
#include <htypes/include/types.hpp>

#include <haf/include/animation/animationcomponent.hpp>
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
    const vector2df& lastTokenPosition)
{
    auto renderizableSceneNode =
        main_node.createSceneNode<RenderizablesSceneNode>(
            "pointIncrementScore_SceneNode");

    auto node = renderizableSceneNode->renderizableBuilder()
                    .name("pointIncrementScore")
                    .figType(FigType_t::Shape)
                    .box(rectFromSize(15.0F, 15.0F))
                    .color(colors::White)
                    .pointCount(30U)
                    .create();

    {
        using namespace gameplay::constants;

        DisplayLog::info("Creating animation for points to score");
        scene_animation_component_->addPropertyAnimation(
            time::TimePoint_as_miliseconds(MillisAnimationPointsToScore),
            renderizableSceneNode->prop<Position>(), lastTokenPosition,
            EndPositionPointsToScore, AnimationDirection::Forward,
            [renderizableSceneNode]() {
                renderizableSceneNode->parentAs<SceneNode>()->removeSceneNode(
                    renderizableSceneNode);
            });
    }
}
}  // namespace zoper
