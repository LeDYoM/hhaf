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
#include <haf/include/scene/scene.hpp>
#include <boardmanager/include/boardmanager.hpp>
#include <boardmanager/include/board_types.hpp>
#include <haf/include/render/renderizable.hpp>
#include <haf/include/time/timercomponent.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/scene_components/statescontrolleractuator.hpp>
#include <haf/include/time/timercomponent.hpp>

#include "../scene_names.hpp"

namespace zoper
{
class NextToken;

class GameScene final : public haf::scene::Scene
{
    using BaseClass = haf::scene::Scene;

public:
    GameScene();
    ~GameScene() override;

    static constexpr char StaticTypeName[] = GAME_SCENE_NAME;

    htps::str nextSceneName() override;
    void onCreated() override;

    htps::sptr<LevelProperties> levelProperties() const noexcept
    {
        return level_properties_;
    }

    void goGameOver();
    void tokenHitAnimation(haf::board::BoardPositionType const& pos);
    void launchPlayer();

private:
    struct GameScenePrivate;
    htps::uptr<GameScenePrivate> p_;

    void generateNextToken();

    htps::sptr<scene::StatesControllerComponent<GameSceneStates>> scene_states_;

    void _debugDisplayBoard() const;

    htps::sptr<BoardGroup> board_group_;

    // Timer related properties
    htps::sptr<time::TimerComponent> scene_timer_component_;
    time::TimerConnectorSPtr next_token_timer_;
    htps::sptr<NextToken> next_token_;

    // General properties.
    htps::u16 next_token_part_{0U};
    htps::sptr<LevelProperties> level_properties_;
};
}  // namespace zoper

#endif
