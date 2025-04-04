#ifndef ZOOPER_GAMESCENE_STATE_MANAGER_INCLUDE_HPP
#define ZOOPER_GAMESCENE_STATE_MANAGER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/scene_components/statescontrolleractuator.hpp>
#include <haf/include/time/timer_component.hpp>
#include "gameover.hpp"
#include "pause.hpp"
#include "gamescene_states.hpp"

namespace zoper
{
class GameSceneStateManager
    : public haf::scene::StatesControllerActuator<GameSceneStates>
{
    using BaseClass = haf::scene::StatesControllerActuator<GameSceneStates>;

public:
    GameSceneStateManager(
        htps::sptr<haf::time::TimerComponent>& scene_timer_component,
        htps::sptr<Pause> pause,
        htps::sptr<GameOver> game_over);

    void onEnterState(GameSceneStates const&) override;
    void onExitState(GameSceneStates const&) override;

private:
    htps::sptr<haf::time::TimerComponent> m_scene_timer_component;
    htps::sptr<Pause> m_pause;
    htps::sptr<GameOver> m_game_over;
};
}  // namespace zoper

#endif
