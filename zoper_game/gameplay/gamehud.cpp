#include "gamehud.hpp"

#include "../loaders/gameresources.hpp"

#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_nodes/scene_node_text.hpp>

#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>

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

void GameHudSceneNode::onAllScoreElementsCreated(htps::vector2dst const)
{
    Font::value_type font{subSystem<res::IResourceRetriever>()
                              ->getTTFont(GameResources::ScoreFontId)
                              ->font(200U)};

    score_quad_->setTableNodeProperty<Font>(font)
        ->setTableNodeProperty<TextColor>(colors::White);
    //        ->setTableNodeProperty<AlignmentSize>(vector2df{0.1F, 0.1F});

    score_quad_->text(vector2dst{0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Level:")
        .put<TextColor>(colors::Blue);
    score_quad_->text(vector2dst{0U, 1})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Score:")
        .put<TextColor>(colors::Blue);

    score_quad_->setLeftTopPositionScale({0.35F, 0.32F});
    score_quad_->for_each_tableSceneNode([](auto const&, auto const& node)
    {
        node->prop<TextBaseSizeProperty>() = TextBaseSize{'A', 6U};
    });
}

void GameHudSceneNode::onAllGoalElementsCreated(htps::vector2dst const)
{
    Font::value_type font{subSystem<res::IResourceRetriever>()
                              ->getTTFont(GameResources::ScoreFontId)
                              ->font(200U)};

    goal_quad_->setTableNodeProperty<Font>(font)
        ->setTableNodeProperty<TextColor>(colors::White);

    goal_quad_->text(vector2dst{0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Current:")
        .put<TextColor>(colors::Blue);
    goal_quad_->text(vector2dst{0U, 1})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Goal:")
        .put<TextColor>(colors::Blue);

    goal_quad_->setRightTopPositionScale({0.35F, 0.32F});
    goal_quad_->for_each_tableSceneNode([](auto const&, auto const& node)
    {
        node->prop<TextBaseSizeProperty>() = TextBaseSize{'A', 8U};
    });
}

bool GameHudSceneNode::setLevel(size_type const level)
{
    if (score_quad_->nodeTableCreated({1U, 0U}))
    {
        score_quad_->text({1U, 0U})->prop<Text>().set(make_str(level + 1U));
        return true;
    }
    return false;
}

bool GameHudSceneNode::setStayCounter(size_type const stayCounter)
{
    if (goal_quad_->nodeTableCreated({1U, 1U}))
    {
        goal_quad_->text({1U, 1U})->prop<Text>().set(make_str(stayCounter));
        return true;
    }
    return false;
}

bool GameHudSceneNode::setConsumedTokens(size_type const consumedTokens)
{
    if (goal_quad_->nodeTableCreated({1U, 0U}))
    {
        goal_quad_->text(vector2dst{1U, 0U})
            ->prop<Text>()
            .set(str::to_str(consumedTokens));

        return true;
    }
    return false;
}

bool GameHudSceneNode::setEllapsedTimeInSeconds(u64 const seconds)
{
    if (goal_quad_->nodeTableCreated({1U, 0U}))
    {
        goal_quad_->text({1U, 0U})->prop<Text>().set(
            str::to_str(static_cast<u16>(seconds)));

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
        score_quad_->text({1U, 1U})->prop<Text>().set(result);
        return true;
    }
    return false;
}
}  // namespace zoper
