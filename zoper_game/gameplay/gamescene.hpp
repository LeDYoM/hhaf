#pragma once

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

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/scene.hpp>
#include <boardmanager/include/boardmodel.hpp>
#include <lib/scene/nodes/textquad.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>
#include <lib/scene/renderizable.hpp>
#include <lib/scene/components/timercomponent.hpp>
#include <lib/scene/components/statescontroller.hpp>
#include <lib/scene/components/statescontrolleractuator.hpp>
#include <lib/scene/components/timercomponent.hpp>

#include <lib/include/scene/iscene.hpp>

namespace zoper
{
class Player;
class Token;
class PauseSceneNode;
class GameOverSceneNode;

using namespace lib;

class GameScene final : public scene::Scene,
                        public StatesControllerActuator<GameSceneStates>
{
public:
    DECLARE_SCENE(GameScene)

    // Inherited via Scene
    void onCreated() override;

    void onEnterState(const GameSceneStates &) override;
    void onExitState(const GameSceneStates &) override;

    vector2df board2Scene(const lib::vector2dst &bPosition) const;

    sptr<LevelProperties> levelProperties() const { return level_properties_; }
    void goGameOver();

private:
    struct GameScenePrivate;
    GameScenePrivate *private_{nullptr};
    using BaseClass = scene::Scene;
    void setLevel(const size_type nv);
    void generateNextToken();
    vector2df board2SceneFactor() const;
    vector2df tileSize() const;
    void for_each_token_in_line(
        const vector2dst &startPosition,
        const Direction &direction,
        function<bool(const vector2dst &, const Direction &)> updatePredicate);

    sptr<StatesController<GameSceneStates>> m_sceneStates;
    sptr<GameSharedData> game_shared_data_;
    void launchPlayer();
    void addPlayer();
    void _debugDisplayBoard() const;

    sptr<BoardGroup> m_boardGroup;

    // Timer related properties
    sptr<scene::TimerComponent> m_sceneTimerComponent;
    scene::TimerConnectorSPtr m_nextTokenTimer;

    // General properties.
    u8 m_nextTokenPart{0};
    sptr<LevelProperties> level_properties_;
    sptr<Player> m_player{nullptr};
    sptr<GameOverSceneNode> m_gameOver;
    sptr<PauseSceneNode> pause_node_;
};
} // namespace zoper

#endif
