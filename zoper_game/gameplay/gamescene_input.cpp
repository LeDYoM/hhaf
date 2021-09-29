#include "gamescene_input.hpp"
#include "gamescene.hpp"
#include "boardgroup.hpp"
#include "player.hpp"

#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_components/scenecontrol.hpp>
#include <hlog/include/hlog.hpp>

using namespace haf;
using namespace haf::scene;
using namespace haf::input;
using namespace htps;

namespace zoper
{
GameSceneInput::GameSceneInput()  = default;
GameSceneInput::~GameSceneInput() = default;

void GameSceneInput::onAttached()
{
    BaseClass::onAttached();

   // Get all necessary external dependencies
    attachedNodeAs<GameScene>()->components().componentOfType(scene_states_);

    LogAsserter::log_assert(scene_states_ != nullptr,
                            "GameSceneInput needs an attached node with a "
                            "StatesControllerComponent<GameSceneStates>>");

    board_group_ =
        attachedNode()->getByNameAs<BoardGroup>(BoardGroup::StaticName);
    LogAsserter::log_assert(board_group_ != nullptr,
                            "GameSceneInput needs a parent with a board group");

    addStateKeyInputFunction(
        GameSceneStates::Playing,
        htps::make_function(this, &GameSceneInput::onKeyPressedPlaying), {});
    addStateKeyInputFunction(
        GameSceneStates::Pause,
        htps::make_function(this, &GameSceneInput::onKeyPressedPause), {});
    addStateKeyInputFunction(
        GameSceneStates::GameOver,
        htps::make_function(this, &GameSceneInput::onKeyPressedGameOver), {});
}

void GameSceneInput::onKeyPressedPlaying(haf::input::Key const& key)
{
    // TODO: Fixme
    KeyMapping keyMapping__;
    KeyMapping* keyMapping = &keyMapping__;

    auto const dir{keyMapping->getDirectionFromKey(key)};
    if (dir.isValid())
    {
        board_group_->player()->movePlayer(dir);
    }
    else if (keyMapping->isLaunchKey(key))
    {
        attachedNodeAs<GameScene>()->launchPlayer();
    }
    else if (keyMapping->isPauseKey(key))
    {
        scene_states_->setState(GameSceneStates::Pause);
    }
}

void GameSceneInput::onKeyPressedPause(haf::input::Key const& key)
{
    // TODO: Fixme
    KeyMapping keyMapping__;
    KeyMapping* keyMapping = &keyMapping__;

    if (keyMapping->isPauseKey(key))
    {
        scene_states_->setState(GameSceneStates::Playing);
    }
}

void GameSceneInput::onKeyPressedGameOver(haf::input::Key const&)
{
    attachedNode()
        ->subsystems()
        .dataWrapper<haf::scene::SceneControl>()
        ->switchToNextScene();
}

}  // namespace zoper
