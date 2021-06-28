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
    htps::sptr<haf::scene::StatesController<GameSceneStates>> sceneStates,
    htps::sptr<BoardGroup> boardGroup)
{
    m_sceneStates = std::move(sceneStates);
    m_boardGroup = std::move(boardGroup);
}

void GameSceneInput::onKeyPressed(haf::input::Key const& key)
{
    DisplayLog::info("Key pressed in GameScene");
    // TODO: Fixme
    KeyMapping keyMapping__;
    KeyMapping* keyMapping = &keyMapping__;

    switch (m_sceneStates->currentState())
    {
        case GameSceneStates::Playing:
        {
            auto dir(keyMapping->getDirectionFromKey(key));
            if (dir.isValid())
            {
                m_boardGroup->player()->movePlayer(dir);
            }
            else if (keyMapping->isLaunchKey(key))
            {
                attachedNodeAs<GameScene>()->launchPlayer();
            }
            else if (keyMapping->isPauseKey(key))
            {
                m_sceneStates->setState(GameSceneStates::Pause);
            }
        }
        break;

        case GameSceneStates::GameOver:
        {
            attachedNode()
                ->dataWrapper<haf::scene::SceneControl>()
                ->switchToNextScene();
        }
        break;

        case GameSceneStates::Pause:
        {
            if (keyMapping->isPauseKey(key))
            {
                m_sceneStates->setState(GameSceneStates::Playing);
            }
        }
        break;
    }
}

void GameSceneInput::onKeyReleased(haf::input::Key const&)
{}

}  // namespace zoper
