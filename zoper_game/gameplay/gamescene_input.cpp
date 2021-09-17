#include "gamescene_input.hpp"
#include "gamescene_private.hpp"
#include "gamescene.hpp"
#include "boardgroup.hpp"
#include "player.hpp"

#include <haf/include/scene_components/scenecontrol.hpp>

namespace zoper
{
GameSceneInput::GameSceneInput()
{}

GameSceneInput::~GameSceneInput() = default;

void GameSceneInput::configure(
    htps::sptr<haf::scene::StatesControllerComponent<GameSceneStates>> sceneStates,
    htps::sptr<BoardGroup> boardGroup)
{
    scene_states_ = std::move(sceneStates);
    board_group_  = std::move(boardGroup);
}

void GameSceneInput::onKeyPressed(haf::input::Key const& key)
{
    DisplayLog::info("Key pressed in GameScene");
    // TODO: Fixme
    KeyMapping keyMapping__;
    KeyMapping* keyMapping = &keyMapping__;

    switch (scene_states_->currentState())
    {
        case GameSceneStates::Playing:
        {
            auto dir(keyMapping->getDirectionFromKey(key));
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
        break;

        case GameSceneStates::GameOver:
        {
            attachedNode()
                ->subsystems()
                .dataWrapper<haf::scene::SceneControl>()
                ->switchToNextScene();
        }
        break;

        case GameSceneStates::Pause:
        {
            if (keyMapping->isPauseKey(key))
            {
                scene_states_->setState(GameSceneStates::Playing);
            }
        }
        break;
    }
}

void GameSceneInput::onKeyReleased(haf::input::Key const&)
{}

}  // namespace zoper
