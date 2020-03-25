#include "gameover.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/scene/include/scene.hpp>
#include <lib/scene_nodes/include/scenenodetext.hpp>
#include <lib/scene_components/include/scenemetrics.hpp>

#include <lib/include/liblog.hpp>
#include <lib/resources/include/iresourceretriever.hpp>
#include <lib/resources/include/ittfont.hpp>
#include <lib/resources/include/resourceview.hpp>

using namespace mtps;

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;

GameOverSceneNode::GameOverSceneNode(scene::SceneNode *const parent, mtps::str name)
    : SceneNode{parent, std::move(name)}
{
    m_gameOverrg = createSceneNode("gameOverScreen");

    vector2df gosize{dataWrapper<SceneMetrics>()->currentView().width, 715};
    m_gameOverrg->position.set({0, 575});
    auto resources_viewer = dataWrapper<ResourceView>();

    auto gameText(m_gameOverrg->createSceneNode<SceneNodeText>("gameovergame"));
    gameText->text.set("GAME");
    gameText->font.set(resources_viewer->getTTFont(GameResources::ScoreFontId)->font(360));
    gameText->textColor = colors::White;
    gameText->alignmentSize.set(gosize);
    gameText->alignmentX.set(SceneNodeText::AlignmentX::Center);
    gameText->alignmentY.set(SceneNodeText::AlignmentY::Top);

    auto overText(m_gameOverrg->createSceneNode<SceneNodeText>("gameoverover"));
    overText->text.set("OVER");
    overText->font.set(resources_viewer->getTTFont(GameResources::ScoreFontId)->font(360));
    overText->textColor = colors::White;
    overText->alignmentSize.set(gosize);
    overText->alignmentX.set(SceneNodeText::AlignmentX::Center);
    overText->alignmentY.set(SceneNodeText::AlignmentY::Bottom);

    visible = false;
}

GameOverSceneNode::~GameOverSceneNode() = default;
} // namespace zoper
