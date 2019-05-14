#include "gamehud.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/scene/scenemanager.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>

#include <lib/scene/components/alignedtextcomponent.hpp>

#include <logger/include/log.hpp>
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
        auto& res_retriever = parentScene()->sceneManager().resources();
        m_scoreQuad = parent->createSceneNode<TextQuad>("score",
            res_retriever.getFont(GameResources::ScoreFontId)->font(90),
            colors::White, vector2df{ 600, 300 });
        m_scoreQuad->position.set(vector2df{ 50, 150 });
        m_scoreQuad->text(vector2dst{ 0,0 })->text.set(Text_t("Level:"));
        m_scoreQuad->text(vector2dst{ 0,0 })->textColor = FillColor_t(colors::Blue);
        m_scoreQuad->text(vector2dst{ 0,1 })->text.set(Text_t("Score:"));
        m_scoreQuad->text(vector2dst{ 0,1 })->textColor = FillColor_t(colors::Blue);

        m_goalQuad = parent->createSceneNode<TextQuad>("goal",
            res_retriever.getFont(GameResources::ScoreFontId)->font(90),
            colors::White, vector2df{ 600, 300 });
        m_goalQuad->position.set(vector2df{ 1250, 50 });
        m_goalQuad->text(vector2dst{ 0,0 })->textColor = FillColor_t(colors::Blue);
        m_goalQuad->text(vector2dst{ 0,1 })->textColor = FillColor_t(colors::Blue);

        m_goalQuad->text(vector2dst{ 0,0 })->text.set(Text_t(
//            gameMode == GameMode::Token ? "Tokens: " : "Time: ")
            "Look here: ")
        );
        m_goalQuad->text(vector2dst{ 0,1 })->text.set(Text_t("Goal: "));
    }

    GameHudSceneNode::~GameHudSceneNode() = default;

    void GameHudSceneNode::setLevel(const size_type level)
    {
        m_scoreQuad->text(vector2dst{ 1,0 })->text.set(Text_t(make_str(level + 1)));
    }

    void GameHudSceneNode::setStayCounter(const size_type stayCounter)
    {
        m_goalQuad->text(vector2dst{ 1,1 })->text.set(Text_t(make_str(stayCounter)));
    }

    void GameHudSceneNode::setConsumedTokens(const size_type consumedTokens)
    {
        m_goalQuad->text(vector2dst{ 1,0 })->text.set(Text_t(consumedTokens));
    }

    void GameHudSceneNode::setEllapsedTimeInSeconds(const u64 seconds)
    {
        m_goalQuad->text(vector2dst{ 1,0 })->text.set(
            Text_t(static_cast<u16>(seconds))
        );
    }

    constexpr u8 scoreSize = 5;

    void GameHudSceneNode::setScore(const size_type score)
    {
        str result(score);
        while (result.size() < scoreSize) result = "0" + result;
        m_scoreQuad->text(vector2dst{ 1,1 })->text.set(Text_t(result));
    }
}
