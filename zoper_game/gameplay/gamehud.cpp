#include "gamehud.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/scene/include/scene.hpp>
#include <haf/scene_nodes/include/scenenodetext.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/resources/include/resourceview.hpp>
#include <haf/resources/include/ittfont.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{
GameHudSceneNode::GameHudSceneNode(
    mtps::rptr<haf::scene::SceneNode> const parent,
    str name) :
    SceneNode{parent, std::move(name)}
{
    auto resources_viewer = dataWrapper<res::ResourceView>();

    m_scoreQuad = parent->createSceneNode<TextQuad>("score");
    m_scoreQuad->configure(
        resources_viewer->getTTFont(GameResources::ScoreFontId)->font(90U),
        colors::White, vector2df{600, 300});
    m_scoreQuad->position.set(vector2df{50, 150});
    m_scoreQuad->text(vector2dst{0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Level:")
        .put<TextColor>(colors::Blue);
    m_scoreQuad->text(vector2dst{0U, 1})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Score:")
        .put<TextColor>(colors::Blue);

    m_goalQuad = parent->createSceneNode<TextQuad>("goal");
    m_goalQuad->configure(
        resources_viewer->getTTFont(GameResources::ScoreFontId)->font(90),
        colors::White, vector2df{600, 300});
    m_goalQuad->position.set(vector2df{1250, 150});
    m_goalQuad->text({0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<TextColor>(colors::Blue)
        .put<Text>("Look here");
    m_goalQuad->text({0U, 1U})
        ->prop<SceneNodeTextProperties>()
        .put<TextColor>(colors::Blue)
        .put<Text>("Goal:");

    //    m_goalQuad->text(vector2dst{0, 0})
    //        ->text.set(
    //            gameMode == GameMode::Token ? "Tokens: " : "Time: ")
    //            "Look here: ");
}

GameHudSceneNode::~GameHudSceneNode() = default;

void GameHudSceneNode::setLevel(const size_type level)
{
    m_scoreQuad->text({1U, 0U})->prop<SceneNodeTextProperties>().set<Text>(
        make_str(level + 1U));
}

void GameHudSceneNode::setStayCounter(const size_type stayCounter)
{
    m_goalQuad->text({1U, 1U})->prop<SceneNodeTextProperties>().set<Text>(
        make_str(stayCounter));
}

void GameHudSceneNode::setConsumedTokens(const size_type consumedTokens)
{
    m_goalQuad->text(vector2dst{1U, 0U})
        ->prop<SceneNodeTextProperties>()
        .set<Text>(str::to_str(consumedTokens));
}

void GameHudSceneNode::setEllapsedTimeInSeconds(const u64 seconds)
{
    m_goalQuad->text({1U, 0U})->prop<SceneNodeTextProperties>().set<Text>(
        str::to_str(static_cast<u16>(seconds)));
}

constexpr u8 scoreSize = 5;

void GameHudSceneNode::setScore(const size_type score)
{
    str result(str::to_str(score));
    while (result.size() < scoreSize)
        result = "0" + result;
    m_scoreQuad->text({1U, 1U})->prop<SceneNodeTextProperties>().set<Text>(result);
}
}  // namespace zoper
