#ifndef ZOOPER_GAMESCENE_STATE_MANAGER_INCLUDE_HPP
#define ZOOPER_GAMESCENE_STATE_MANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/scene_components/statescontrolleractuator.hpp>
#include <haf/include/time/timer_component.hpp>

#include "gamescene_states.hpp"

namespace zoper
{
class PauseSceneNode;
class GameOverSceneNode;

class GameSceneStateManager
    : public haf::scene::StatesControllerActuator<GameSceneStates>
{
    using BaseClass = haf::scene::StatesControllerActuator<GameSceneStates>;

public:
    GameSceneStateManager(
        htps::sptr<haf::time::TimerComponent>& scene_timer_component,
        htps::sptr<PauseSceneNode> pause_scene_node,
        htps::sptr<GameOverSceneNode> game_over_scene_node);

    void onEnterState(GameSceneStates const&) override;
    void onExitState(GameSceneStates const&) override;

private:
    htps::sptr<haf::time::TimerComponent> scene_timer_component_;
    htps::sptr<PauseSceneNode> pause_node_;
    htps::sptr<GameOverSceneNode> game_over_scene_node_;
};
}  // namespace zoper

#endif
