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
    score_quad_ = parent()->createSceneNode<TextQuad>("score");
    goal_quad_  = parent()->createSceneNode<TextQuad>("goal");

    score_quad_->allElementsCreated +=
        make_function(this, &GameHudSceneNode::onAllScoreElementsCreated);
    goal_quad_->allElementsCreated +=
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

void GameHudSceneNode::onAllScoreElementsCreated()
{
    Font::value_type font{subSystem<res::IResourceRetriever>()
                              ->getTTFont(GameResources::ScoreFontId)
                              ->font(200U)};

    score_quad_->setTableNodeProperty<Font>(font)
        ->setTableNodeProperty<TextColor>(colors::White)
        ->setTableNodeProperty<AlignmentSize>(vector2df{0.1F, 0.1F});

    score_quad_->prop<Position>() = Position::value_type{-0.45F, -0.33F};
    score_quad_->text(vector2dst{0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Level:")
        .put<TextColor>(colors::Blue);
    score_quad_->text(vector2dst{0U, 1})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Score:")
        .put<TextColor>(colors::Blue);

    score_quad_->prop<Scale>() = vector2df{0.15F, 0.25F};
}

void GameHudSceneNode::onAllGoalElementsCreated()
{
    Font::value_type font{subSystem<res::IResourceRetriever>()
                              ->getTTFont(GameResources::ScoreFontId)
                              ->font(200U)};

    goal_quad_->setTableNodeProperty<Font>(font)
        ->setTableNodeProperty<TextColor>(colors::White)
        ->setTableNodeProperty<AlignmentSize>(vector2df{0.1F, 0.1F});

    goal_quad_->prop<Position>() = Position::value_type{0.2F, -0.33F};
    goal_quad_->text(vector2dst{0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Current:")
        .put<TextColor>(colors::Blue);
    goal_quad_->text(vector2dst{0U, 1})
        ->prop<SceneNodeTextProperties>()
        .put<Text>("Goal:")
        .put<TextColor>(colors::Blue);

    goal_quad_->prop<Scale>() = vector2df{0.15F, 0.25F};
}

bool GameHudSceneNode::setLevel(size_type const level)
{
    if (score_quad_->nodeTableCreated({1U, 0U}))
    {
        score_quad_->text({1U, 0U})->prop<Text>().set(make_str(level + 1U));
        // TODO: Big nyapa
        score_quad_->text({1U, 0U})->prop<Position>().set({1.0F, 0.0F});
        return true;
    }
    return false;
}

bool GameHudSceneNode::setStayCounter(size_type const stayCounter)
{
    if (goal_quad_->nodeTableCreated({1U, 1U}))
    {
        goal_quad_->text({1U, 1U})->prop<Text>().set(make_str(stayCounter));
        // TODO: Big nyapa
        goal_quad_->text({1U, 1U})->prop<Position>().set({1.0F, 0.0F});
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
        // TODO: Big nyapa
        goal_quad_->text({1U, 0U})->prop<Position>().set({1.0F, 0.0F});

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
        // TODO: Big nyapa
        goal_quad_->text({1U, 0U})->prop<Position>().set({1.0F, 0.0F});

        return true;
    }
    return false;
}

constexpr u8 scoreSize = 5;

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
        // TODO: Big nyapa
        score_quad_->text({1U, 1U})->prop<Position>().set({1.0F, 0.0F});
        return true;
    }
    return false;
}
}  // namespace zoper
