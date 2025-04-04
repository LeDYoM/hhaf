#ifndef ZOOPER_GAMESCENE_INCLUDE_HPP
#define ZOOPER_GAMESCENE_INCLUDE_HPP

#include "direction.hpp"
#include "levelproperties.hpp"
#include "boardgroup.hpp"
#include "tokenzones.hpp"
#include "gamescene_states.hpp"

#include "../keymapping.hpp"
#include "../gameshareddata.hpp"
#include "../loaders/gameresources.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/function.hpp>
#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/board_types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/time/timer_component.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/scene_components/statescontrolleractuator.hpp>
#include <haf/include/scene_components/scene_component.hpp>
#include <haf/include/time/timer_component.hpp>

#include "../scene_names.hpp"

namespace zoper
{
class NextToken;

class Game final : public haf::scene::SceneComponent
{
    using Base = haf::scene::SceneComponent;

public:
    Game();
    ~Game() override;

    static constexpr char StaticTypeName[] = GAME_SCENE_NAME;

    htps::str nextSceneName() override;
    void onAttached() override;

    htps::sptr<LevelProperties> levelProperties() const noexcept;

    void goGameOver();
    void tokenHitAnimation(haf::board::BoardPositionType const& pos);
    void launchPlayer();

private:
    struct GameScenePrivate;
    htps::uptr<GameScenePrivate> p_;

    void generateNextToken();
    void _debugDisplayBoard() const;

    htps::sptr<scene::StatesControllerComponent<GameSceneStates>> m_scene_states;
    htps::sptr<BoardGroup> m_board_group;

    // Timer related properties
    htps::sptr<time::TimerComponent> m_scene_timer_component;
    time::TimerConnectorSPtr m_next_token_timer;
    htps::sptr<NextToken> m_next_token;

    // General properties.
    htps::u16 m_next_token_part{0U};
    htps::sptr<LevelProperties> m_level_properties;
};
}  // namespace zoper

#endif
