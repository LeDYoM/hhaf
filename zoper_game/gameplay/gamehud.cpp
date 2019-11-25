#include "gamehud.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/scene/scenemanager.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>

#include <lib/scene/components/alignedtextcomponent.hpp>

#include <lib/include/liblog.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>
#include <lib/include/resources/iresourceretriever.hpp>
#include <lib/resources/ttfont.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
    using namespace lib::scene::nodes;

    GameHudSceneNode::GameHudSceneNode(SceneNode * const parent, str name)
        : SceneNode{parent, std::move(name)}
    {
        auto resources_viewer = dataWrapper<ResourceView>();

        m_scoreQuad = parent->createSceneNode<TextQuad>("score",
            resources_viewer->getTTFont(GameResources::ScoreFontId)->font(90U),
            colors::White, vector2df{ 600, 300 });
        m_scoreQuad->position.set(vector2df{ 50, 150 });
        m_scoreQuad->text(vector2dst{ 0,0 })->text.set("Level:");
        m_scoreQuad->text(vector2dst{ 0,0 })->textColor = colors::Blue;
        m_scoreQuad->text(vector2dst{ 0,1 })->text.set("Score:");
        m_scoreQuad->text(vector2dst{ 0,1 })->textColor = colors::Blue;

        m_goalQuad = parent->createSceneNode<TextQuad>("goal",
            resources_viewer->getTTFont(GameResources::ScoreFontId)->font(90),
            colors::White, vector2df{ 600, 300 });
        m_goalQuad->position.set(vector2df{ 1250, 150 });
        m_goalQuad->text(vector2dst{ 0,0 })->textColor = colors::Blue;
        m_goalQuad->text(vector2dst{ 0,1 })->textColor = colors::Blue;

        m_goalQuad->text(vector2dst{ 0,0 })->text.set(
//            gameMode == GameMode::Token ? "Tokens: " : "Time: ")
            "Look here: ");
        m_goalQuad->text(vector2dst{ 0,1 })->text.set("Goal: ");
    }

    GameHudSceneNode::~GameHudSceneNode() = default;

    void GameHudSceneNode::setLevel(const size_type level)
    {
        m_scoreQuad->text(vector2dst{ 1,0 })->text.set(make_str(level + 1));
    }

    void GameHudSceneNode::setStayCounter(const size_type stayCounter)
    {
        m_goalQuad->text(vector2dst{ 1,1 })->text.set(make_str(stayCounter));
    }

    void GameHudSceneNode::setConsumedTokens(const size_type consumedTokens)
    {
        str comsumed_tokens_str{str::to_str(consumedTokens)};
        m_goalQuad->text(vector2dst{ 1,0 })->text.set(str::to_str(consumedTokens));
    }

    void GameHudSceneNode::setEllapsedTimeInSeconds(const u64 seconds)
    {
        m_goalQuad->text(vector2dst{ 1,0 })->text.set(
            str::to_str(static_cast<u16>(seconds))
        );
    }

    constexpr u8 scoreSize = 5;

    void GameHudSceneNode::setScore(const size_type score)
    {
        str result(str::to_str(score));
        while (result.size() < scoreSize) result = "0" + result;
        m_scoreQuad->text(vector2dst{ 1,1 })->text.set(result);
    }
}
