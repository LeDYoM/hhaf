#include "gamehud.hpp"

#include "../loaders/gameresources.hpp"

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <htypes/include/function.hpp>
#include <haf/include/properties/properties.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace fmath;

namespace zoper
{
void GameHud::onAttached()
{
    m_score_quad = attachedNode()->createSceneNode("score")->component<TableOfTextQuad>();
    m_goal_quad  = attachedNode()->createSceneNode("goal")->component<TableOfTextQuad>();

    m_score_quad->allTableElementsCreated +=
        make_function(this, &GameHud::onAllScoreElementsCreated);
    m_goal_quad->allTableElementsCreated +=
        make_function(this, &GameHud::onAllGoalElementsCreated);
}

void GameHud::update()
{
    Base::update();

    if (currentLevel.hasChanged())
    {
        if (setLevel(currentLevel()))
        {
            currentLevel.resetHasChanged();
        }
    }

    if (currentScore.hasChanged())
    {
        if (setScore(currentScore()))
        {
            currentScore.resetHasChanged();
        }
    }

    if (currentConsumedTokens.hasChanged())
    {
        if (setConsumedTokens(currentConsumedTokens()))
        {
            currentConsumedTokens.resetHasChanged();
        }
    }

    if (currentEllapsedTimeInSeconds.hasChanged())
    {
        if (setEllapsedTimeInSeconds(currentEllapsedTimeInSeconds()))
        {
            currentEllapsedTimeInSeconds.resetHasChanged();
        }
    }

    if (currentStayCounter.hasChanged())
    {
        if (setStayCounter(currentStayCounter()))
        {
            currentStayCounter.resetHasChanged();
        }
    }
}

void GameHud::setCurrentConsumedTokens(const htps::size_type a)
{
    currentConsumedTokens.assignIfDifferent(a);
}

void GameHud::onAllScoreElementsCreated(fmath::vector2dst const)
{
    auto font{attachedNode()->subSystem<res::IResourceRetriever>()
                  ->getTTFont(GameResources::ScoreFontId)
                  ->font(200U)};

    m_score_quad->set_property_for_each_table_node(&Text::Font, font);
    m_score_quad->set_property_for_each_table_node(&Text::TextColor,
                                                  colors::White);

    auto text_00{m_score_quad->text(vector2dst{0U, 0U})};
    text_00->Text      = "Level:";
    text_00->TextColor = colors::Blue;

    auto text_01{m_score_quad->text(vector2dst{0U, 1U})};
    text_01->Text      = "Score:";
    text_01->TextColor = colors::Blue;

    m_score_quad->attachedNode()->setLeftTopPositionScale({0.35F, 0.32F});
    m_score_quad->for_each_outerSceneNode([](auto const&, auto const& node) {
        node->TextBaseSizeProperty = TextBaseSize{'A', 6U};
    });
}

void GameHud::onAllGoalElementsCreated(fmath::vector2dst const)
{
    auto font{attachedNode()->subSystem<res::IResourceRetriever>()
                  ->getTTFont(GameResources::ScoreFontId)
                  ->font(200U)};

    m_goal_quad->set_property_for_each_table_node(&Text::Font, font);
    m_goal_quad->set_property_for_each_table_node(&Text::TextColor,
                                                 colors::White);

    auto text_00{m_goal_quad->text(vector2dst{0U, 0U})};
    text_00->Text      = "Current:";
    text_00->TextColor = colors::Blue;

    auto text_01{m_goal_quad->text(vector2dst{0U, 1U})};
    text_01->Text      = "Goal:";
    text_01->TextColor = colors::Blue;

    m_goal_quad->attachedNode()->setRightTopPositionScale({0.35F, 0.32F});
    m_goal_quad->for_each_outerSceneNode([](auto const&, auto const& node) {
        node->TextBaseSizeProperty = TextBaseSize{'A', 8U};
    });
}

bool GameHud::setLevel(size_type const level)
{
    if (m_score_quad->nodeTableCreated({1U, 0U}))
    {
        m_score_quad->text({1U, 0U})->Text = make_str(level + 1U);
        return true;
    }
    return false;
}

bool GameHud::setStayCounter(size_type const stayCounter)
{
    if (m_goal_quad->nodeTableCreated({1U, 1U}))
    {
        m_goal_quad->text({1U, 1U})->Text = make_str(stayCounter);
        return true;
    }
    return false;
}

bool GameHud::setConsumedTokens(size_type const consumedTokens)
{
    if (m_goal_quad->nodeTableCreated({1U, 0U}))
    {
        m_goal_quad->text(vector2dst{1U, 0U})->Text =
            str::to_str(consumedTokens);

        return true;
    }
    return false;
}

bool GameHud::setEllapsedTimeInSeconds(u64 const seconds)
{
    if (m_goal_quad->nodeTableCreated({1U, 0U}))
    {
        m_goal_quad->text({1U, 0U})->Text =
            str::to_str(static_cast<u16>(seconds));

        return true;
    }
    return false;
}

constexpr fast_u8 scoreSize{3U};

bool GameHud::setScore(size_type const score)
{
    if (m_score_quad->nodeTableCreated({1U, 1U}))
    {
        str result(str::to_str(score));
        while (result.size() < scoreSize)
        {
            result = "0" + result;
        }
        m_score_quad->text({1U, 1U})->Text = result;
        return true;
    }
    return false;
}
}  // namespace zoper
