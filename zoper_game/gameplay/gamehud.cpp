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
}

void GameHudSceneNode::onAllGoalElementsCreated()
{
    Font::value_type font{subSystem<res::IResourceRetriever>()
                              ->getTTFont(GameResources::ScoreFontId)
                              ->font(46U)};

    goal_quad_->setTableNodeProperty<Font>(font)
        ->setTableNodeProperty<TextColor>(colors::White)
        ->setTableNodeProperty<AlignmentSize>(vector2df{600, 300});

    goal_quad_->prop<Position>().set(vector2df{1250, 150});
    goal_quad_->text({0U, 0U})
        ->prop<SceneNodeTextProperties>()
        .put<TextColor>(colors::Blue)
        .put<Text>("Current:");
    goal_quad_->text({0U, 1U})
        ->prop<SceneNodeTextProperties>()
        .put<TextColor>(colors::Blue)
        .put<Text>("Goal:");

    //    goal_quad->text(vector2dst{0, 0})
    //        ->text.set(
    //            gameMode == GameMode::Token ? "Tokens: " : "Time: ")
    //            "Look here: ");
}

bool GameHudSceneNode::setLevel(const size_type level)
{
    if (score_quad_->nodeTableCreated({1U, 0U}))
    {
        score_quad_->text({1U, 0U})->prop<Text>().set(make_str(level + 1U));
        return true;
    }
    return false;
}

void GameHudSceneNode::setStayCounter(const size_type /*stayCounter*/)
{
    //    goal_quad_->text({1U, 1U})->prop<Text>().set(make_str(stayCounter));
}

void GameHudSceneNode::setConsumedTokens(const size_type /*consumedTokens*/)
{
    //    goal_quad_->text(vector2dst{1U, 0U})
    //        ->prop<Text>()
    //        .set(str::to_str(consumedTokens));
}

void GameHudSceneNode::setEllapsedTimeInSeconds(const u64 /*seconds*/)
{
    //    goal_quad_->text({1U, 0U})->prop<Text>().set(
    //        str::to_str(static_cast<u16>(seconds)));
}

constexpr u8 scoreSize = 5;

void GameHudSceneNode::setScore(const size_type score)
{
    str result(str::to_str(score));
    while (result.size() < scoreSize)
        result = "0" + result;
    //    score_quad_->text({1U, 1U})->prop<Text>().set(result);
}
}  // namespace zoper
