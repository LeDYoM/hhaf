#include "gameover.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/iresource_retriever.hpp>

using namespace htps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

void GameOverSceneNode::onCreated()
{
    game_over_rg_ = createSceneNode<TransformableSceneNode>("gameOverScreen");

    {
        auto gameText(
            game_over_rg_->createSceneNode<SceneNodeText>("gameovergame"));
        gameText->prop<SceneNodeTextProperties>()
            .put<Text>("GAME")
            .put<Font>(subSystem<res::IResourceRetriever>()
                           ->getTTFont(GameResources::ScoreFontId)
                           ->font(100))
            .put<TextColor>(colors::White);
        gameText->prop<TransformationProperties>()
            .put<Scale>({0.3F, 0.3F})
            .put<Position>({0.0F, -0.15F});
    }

    {
        auto overText(
            game_over_rg_->createSceneNode<SceneNodeText>("gameoverover"));
        overText->prop<SceneNodeTextProperties>()
            .put<Text>("OVER")
            .put<Font>(subSystem<res::IResourceRetriever>()
                           ->getTTFont(GameResources::ScoreFontId)
                           ->font(100))
            .put<TextColor>(colors::White);
        overText->prop<TransformationProperties>()
            .put<Scale>({0.3F, 0.3F})
            .put<Position>({0.0F, 0.15F});
    }

    prop<Visible>().set(false);
}

}  // namespace zoper
