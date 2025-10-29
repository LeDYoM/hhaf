#include "gameover.hpp"

#include "../loaders/gameresources.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/scene_components/text.hpp>

using namespace htps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;

void GameOver::onAttached()
{
    m_game_over_rg = attachedNode()->createSceneNode("gameOverScreen");

    {
        auto gameText{
            m_game_over_rg->createSceneNode("gameovergame")->component<Text>()};
        gameText->Text = "GAME";
        gameText->Font = attachedNode()->subSystem<res::IResourceRetriever>()
                             ->getTTFont(GameResources::ScoreFontId)
                             ->font(100);
        gameText->TextColor = colors::White;
        auto transformation_node{gameText->attachedNode()->component<Transformation>()};
        transformation_node->Scale     = {0.3F, 0.3F};
        transformation_node->Position  = {0.0F, -0.15F};
    }

    {
        auto overText{
            m_game_over_rg->createSceneNode("gameoverover")->component<Text>()};
        overText->Text = "OVER";
        overText->Font = attachedNode()->subSystem<res::IResourceRetriever>()
                             ->getTTFont(GameResources::ScoreFontId)
                             ->font(100);
        overText->TextColor = colors::White;
        auto transformation_node{overText->attachedNode()->component<Transformation>()};
        transformation_node->Scale     = {0.3F, 0.3F};
        transformation_node->Position  = {0.0F, 0.15F};
    }

    attachedNode()->Enabled = false;
}

}  // namespace zoper
