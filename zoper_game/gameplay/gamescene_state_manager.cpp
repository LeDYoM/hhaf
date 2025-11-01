#include "gamescene_state_manager.hpp"
#include "pause.hpp"
#include "gameover.hpp"
#include "gamescene_states.hpp"

#include <hlog/include/hlog.hpp>

using namespace haf;
using namespace haf::scene;

using namespace htps;

namespace zoper
{
GameSceneStateManager::GameSceneStateManager(
    sptr<haf::time::TimerComponent>& scene_timer_component,
    sptr<Pause> pause,
    sptr<GameOver> game_over) :
    m_scene_timer_component{scene_timer_component},
    m_pause{htps::move(pause)},
    m_game_over{htps::move(game_over)}
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
            m_scene_timer_component->pause();
            m_pause->enterPause();
        }
        break;
        case GameSceneStates::GameOver:
        {
            m_game_over->attachedNode()->Visible = true;
            m_scene_timer_component->pause();
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
            m_scene_timer_component->resume();
            m_pause->exitPause();
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
