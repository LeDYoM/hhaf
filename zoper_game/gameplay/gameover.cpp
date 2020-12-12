#include "gameover.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/scene/include/scene.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>
#include <haf/scene_components/include/scenemetricsview.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/resources/include/ittfont.hpp>
#include <haf/resources/include/iresourceretriever.hpp>

using namespace mtps;

namespace zoper
{
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

GameOverSceneNode::GameOverSceneNode(scene::SceneNode* const parent, str name) :
    SceneNode{parent, std::move(name)}
{
    m_gameOverrg = createSceneNode("gameOverScreen");

    vector2df gosize{dataWrapper<SceneMetricsView>()->currentView().width, 715};
    m_gameOverrg->prop<Position>() = Position::value_type{0, 575};

    {
        auto gameText(
            m_gameOverrg->createSceneNode<SceneNodeText>("gameovergame"));
        gameText->prop<SceneNodeTextProperties>()
            .put<Text>("GAME")
            .put<Font>(systemInterface<res::IResourceRetriever>()
                           .getTTFont(GameResources::ScoreFontId)
                           ->font(360))
            .put<TextColor>(colors::White)
            .put<AlignmentSize>(gosize)
            .put<AlignmentX>(AlignmentXModes::Center)
            .put<AlignmentY>(AlignmentYModes::Top);
    }

    {
        auto overText(
            m_gameOverrg->createSceneNode<SceneNodeText>("gameoverover"));
        overText->prop<SceneNodeTextProperties>()
            .put<Text>("OVER")
            .put<Font>(systemInterface<res::IResourceRetriever>()
                           .getTTFont(GameResources::ScoreFontId)
                           ->font(360))
            .put<TextColor>(colors::White)
            .put<AlignmentSize>(gosize)
            .put<AlignmentX>(AlignmentXModes::Center)
            .put<AlignmentY>(AlignmentYModes::Bottom);
    }

    prop<Visible>().set(false);
}

GameOverSceneNode::~GameOverSceneNode() = default;
}  // namespace zoper
