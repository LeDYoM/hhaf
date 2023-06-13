#include "gamehud.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <htypes/include/function.hpp>
#include <haf/include/properties/properties.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{
void GameHudSceneNode::onCreated()
{
    score_quad_ = createSceneNode<TextQuad>("score");
    goal_quad_  = createSceneNode<TextQuad>("goal");

    score_quad_->allTableElementsCreated +=
        make_function(this, &GameHudSceneNode::onAllScoreElementsCreated);
    goal_quad_->allTableElementsCreated +=
        make_function(this, &GameHudSceneNode::onAllGoalElementsCreated);
}

void GameHudSceneNode::update()
{
    BaseClass::update();

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

void GameHudSceneNode::onAllScoreElementsCreated(fmath::vector2dst const)
{
    auto font{subSystem<res::IResourceRetriever>()
                  ->getTTFont(GameResources::ScoreFontId)
                  ->font(200U)};

    score_quad_->set_property_for_each_table_node(&SceneNodeText::Font, font);
    score_quad_->set_property_for_each_table_node(&SceneNodeText::TextColor,
                                                 colors::White);

    auto text_00{score_quad_->text(vector2dst{0U, 0U})};
    text_00->Text      = "Level:";
    text_00->TextColor = colors::Blue;

    auto text_01{score_quad_->text(vector2dst{0U, 1U})};
    text_01->Text      = "Score:";
    text_01->TextColor = colors::Blue;

    score_quad_->setLeftTopPositionScale({0.35F, 0.32F});
    score_quad_->for_each_tableSceneNode([](auto const&, auto const& node) {
        node->TextBaseSizeProperty = TextBaseSize{'A', 6U};
    });
}

void GameHudSceneNode::onAllGoalElementsCreated(fmath::vector2dst const)
{
    auto font{subSystem<res::IResourceRetriever>()
                  ->getTTFont(GameResources::ScoreFontId)
                  ->font(200U)};

    goal_quad_->set_property_for_each_table_node(&SceneNodeText::Font, font);
    goal_quad_->set_property_for_each_table_node(&SceneNodeText::TextColor,
                                                 colors::White);

    auto text_00{goal_quad_->text(vector2dst{0U, 0U})};
    text_00->Text      = "Current:";
    text_00->TextColor = colors::Blue;

    auto text_01{goal_quad_->text(vector2dst{0U, 1U})};
    text_01->Text      = "Goal:";
    text_01->TextColor = colors::Blue;

    goal_quad_->setRightTopPositionScale({0.35F, 0.32F});
    goal_quad_->for_each_tableSceneNode([](auto const&, auto const& node) {
        node->TextBaseSizeProperty = TextBaseSize{'A', 8U};
    });
}

bool GameHudSceneNode::setLevel(size_type const level)
{
    if (score_quad_->nodeTableCreated({1U, 0U}))
    {
        score_quad_->text({1U, 0U})->Text = make_str(level + 1U);
        return true;
    }
    return false;
}

bool GameHudSceneNode::setStayCounter(size_type const stayCounter)
{
    if (goal_quad_->nodeTableCreated({1U, 1U}))
    {
        goal_quad_->text({1U, 1U})->Text = make_str(stayCounter);
        return true;
    }
    return false;
}

bool GameHudSceneNode::setConsumedTokens(size_type const consumedTokens)
{
    if (goal_quad_->nodeTableCreated({1U, 0U}))
    {
        goal_quad_->text(vector2dst{1U, 0U})->Text =
            str::to_str(consumedTokens);

        return true;
    }
    return false;
}

bool GameHudSceneNode::setEllapsedTimeInSeconds(u64 const seconds)
{
    if (goal_quad_->nodeTableCreated({1U, 0U}))
    {
        goal_quad_->text({1U, 0U})->Text =
            str::to_str(static_cast<u16>(seconds));

        return true;
    }
    return false;
}

constexpr fast_u8 scoreSize{3U};

bool GameHudSceneNode::setScore(size_type const score)
{
    if (score_quad_->nodeTableCreated({1U, 1U}))
    {
        str result(str::to_str(score));
        while (result.size() < scoreSize)
        {
            result = "0" + result;
        }
        score_quad_->text({1U, 1U})->Text = result;
        return true;
    }
    return false;
}
}  // namespace zoper
