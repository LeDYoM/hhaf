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
        gameText->Text = "GAME";
        gameText->Font = subSystem<res::IResourceRetriever>()
                             ->getTTFont(GameResources::ScoreFontId)
                             ->font(100);
        gameText->TextColor = colors::White;
        gameText->Scale     = {0.3F, 0.3F};
        gameText->Position  = {0.0F, -0.15F};
    }

    {
        auto overText(
            game_over_rg_->createSceneNode<SceneNodeText>("gameoverover"));
        overText->Text = "OVER";
        overText->Font = subSystem<res::IResourceRetriever>()
                             ->getTTFont(GameResources::ScoreFontId)
                             ->font(100);
        overText->TextColor = colors::White;
        overText->Scale     = {0.3F, 0.3F};
        overText->Position  = {0.0F, 0.15F};
    }

    Visible = false;
}

}  // namespace zoper
