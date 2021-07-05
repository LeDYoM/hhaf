#include "gamehud.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scenenodetext.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/resourceretriever.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{
GameHudSceneNode::GameHudSceneNode(
    htps::rptr<haf::scene::SceneNode> const parent,
    str name) :
    BaseClass{parent, std::move(name)}
{
    Font::value_type font{subsystems().dataWrapper<res::ResourceRetriever>()
                                ->getTTFont(GameResources::ScoreFontId)
                                ->font(90U)};
    (m_scoreQuad = parent->createSceneNode<TextQuad>("score"))
        ->setTableNodeProperty<Font>(font)
        ->setTableNodeProperty<TextColor>(colors::White)
        ->setTableNodeProperty<AlignmentSize>(vector2df{600, 300});

    m_scoreQuad->prop<Position>() = Position::value_type{50, 150};
    m_scoreQuad->text(vector2dst{0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Level:")
        .put<TextColor>(colors::Blue);
    m_scoreQuad->text(vector2dst{0U, 1})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Score:")
        .put<TextColor>(colors::Blue);

    (m_goalQuad = parent->createSceneNode<TextQuad>("goal"))
        ->setTableNodeProperty<Font>(font)
        ->setTableNodeProperty<TextColor>(colors::White)
        ->setTableNodeProperty<AlignmentSize>(vector2df{600, 300});

    m_goalQuad->prop<Position>().set(vector2df{1250, 150});
    m_goalQuad->text({0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<TextColor>(colors::Blue)
        .put<Text>("Current");
    m_goalQuad->text({0U, 1U})
        ->prop<SceneNodeTextProperties>()
        .put<TextColor>(colors::Blue)
        .put<Text>("Goal:");

    //    m_goalQuad->text(vector2dst{0, 0})
    //        ->text.set(
    //            gameMode == GameMode::Token ? "Tokens: " : "Time: ")
    //            "Look here: ");
}

void GameHudSceneNode::setLevel(const size_type level)
{
    m_scoreQuad->text({1U, 0U})->prop<Text>().set(make_str(level + 1U));
}

void GameHudSceneNode::setStayCounter(const size_type stayCounter)
{
    m_goalQuad->text({1U, 1U})->prop<Text>().set(make_str(stayCounter));
}

void GameHudSceneNode::setConsumedTokens(const size_type consumedTokens)
{
    m_goalQuad->text(vector2dst{1U, 0U})
        ->prop<Text>()
        .set(str::to_str(consumedTokens));
}

void GameHudSceneNode::setEllapsedTimeInSeconds(const u64 seconds)
{
    m_goalQuad->text({1U, 0U})->prop<Text>().set(
        str::to_str(static_cast<u16>(seconds)));
}

constexpr u8 scoreSize = 5;

void GameHudSceneNode::setScore(const size_type score)
{
    str result(str::to_str(score));
    while (result.size() < scoreSize)
        result = "0" + result;
    m_scoreQuad->text({1U, 1U})->prop<Text>().set(result);
}
}  // namespace zoper
