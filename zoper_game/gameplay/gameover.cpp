#include "gameover.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>
#include <haf/include/scene_components/scenemetricsview.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/resourceretriever.hpp>

using namespace htps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

GameOverSceneNode::GameOverSceneNode(scene::SceneNode* const parent, str name) :
    BaseClass{parent, std::move(name)}
{
    game_over_rg_ = createSceneNode<TransformableSceneNode>("gameOverScreen");

    vector2df gosize{systemInterface<ISceneMetricsView>().currentView().width,
                     715};
    game_over_rg_->prop<Position>() = Position::value_type{0, 575};

    {
        auto gameText(
            game_over_rg_->createSceneNode<SceneNodeText>("gameovergame"));
        gameText->prop<SceneNodeTextProperties>()
            .put<Text>("GAME")
            .put<Font>(dataWrapper<res::ResourceRetriever>()
                           ->getTTFont(GameResources::ScoreFontId)
                           ->font(360))
            .put<TextColor>(colors::White)
            .put<AlignmentSize>(gosize)
            .put<AlignmentX>(AlignmentXModes::Center)
            .put<AlignmentY>(AlignmentYModes::Top);
    }

    {
        auto overText(
            game_over_rg_->createSceneNode<SceneNodeText>("gameoverover"));
        overText->prop<SceneNodeTextProperties>()
            .put<Text>("OVER")
            .put<Font>(dataWrapper<res::ResourceRetriever>()
                           ->getTTFont(GameResources::ScoreFontId)
                           ->font(360))
            .put<TextColor>(colors::White)
            .put<AlignmentSize>(gosize)
            .put<AlignmentX>(AlignmentXModes::Center)
            .put<AlignmentY>(AlignmentYModes::Bottom);
    }

    prop<Visible>().set(false);
}

}  // namespace zoper
