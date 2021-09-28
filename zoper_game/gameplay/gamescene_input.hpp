#ifndef ZOOPER_GAMESCENE_INPUT_INCLUDE_HPP
#define ZOOPER_GAMESCENE_INPUT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/input/virtual_input_component.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>
#include "gamescene_states.hpp"

namespace zoper
{
class BoardGroup;

class GameSceneInput final : public haf::input::VirtualInputComponent
{
public:
    GameSceneInput();
    ~GameSceneInput() override;

private:
    void onKeyPressed(haf::input::Key const&) override;
    void onKeyReleased(haf::input::Key const&) override;

    void onKeyPressedPlaying(haf::input::Key const&);
    void onKeyPressedPause(haf::input::Key const&);
    void onKeyPressedGameOver(haf::input::Key const&);

    void onAttached() override;

    htps::sptr<haf::scene::StatesControllerComponent<GameSceneStates>>
        scene_states_;
    htps::sptr<BoardGroup> board_group_;
};
}  // namespace zoper

#endif
