#ifndef ZOOPER_GAMESCENE_INPUT_INCLUDE_HPP
#define ZOOPER_GAMESCENE_INPUT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/input/virtual_input_component.hpp>
#include <haf/include/scene_components/statescontroller.hpp>
#include "gamescene_states.hpp"

namespace zoper
{
class BoardGroup;

class GameSceneInput final : public haf::input::VirtualInputComponent
{
public:
    GameSceneInput();
    ~GameSceneInput();

    void configure(
        htps::sptr<haf::scene::StatesController<GameSceneStates>> sceneStates,
        htps::sptr<BoardGroup> boardGroup);

private:
    void onKeyPressed(haf::input::Key const&) override;
    void onKeyReleased(haf::input::Key const&) override;

    htps::sptr<haf::scene::StatesController<GameSceneStates>> scene_states_;
    htps::sptr<BoardGroup> board_group_;
};
}  // namespace zoper

#endif
