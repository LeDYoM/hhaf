#include "gamescene_state_manager.hpp"
#include "pause.hpp"
#include "gameover.hpp"
#include "gamescene_states.hpp"

#include <haf/include/scene/scenenode_properties.hpp>

#include <hlog/include/hlog.hpp>

using namespace haf;
using namespace haf::scene;

using namespace htps;

namespace zoper
{
GameSceneStateManager::GameSceneStateManager(
    sptr<haf::time::TimerComponent>& scene_timer_component,
    sptr<PauseSceneNode> pause_scene_node,
    sptr<GameOverSceneNode> game_over_scene_node) :
    scene_timer_component_{scene_timer_component},
    pause_node_{std::move(pause_scene_node)},
    game_over_scene_node_{std::move(game_over_scene_node)}
{}

void GameSceneStateManager::onEnterState(GameSceneStates const& state)
{
    switch (state)
    {
        case GameSceneStates::Playing:
        {
        }
        break;

        case GameSceneStates::Pause:
        {
            scene_timer_component_->pause();
            pause_node_->enterPause();
        }
        break;
        case GameSceneStates::GameOver:
        {
            game_over_scene_node_->prop<Visible>().set(true);
            scene_timer_component_->pause();
        }
        break;
    }
    DisplayLog::info("Entered state: ", make_str(state));
}

void GameSceneStateManager::onExitState(GameSceneStates const& state)
{
    switch (state)
    {
        case GameSceneStates::Playing:
        {
        }
        break;

        case GameSceneStates::Pause:
        {
            scene_timer_component_->resume();
            pause_node_->exitPause();
        }
        break;

        case GameSceneStates::GameOver:
        {
        }
        break;
    }
    DisplayLog::info("Exited state: ", make_str(state));
}

}  // namespace zoper
