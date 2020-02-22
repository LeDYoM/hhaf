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
#include <lib/scene/include/scene.hpp>
#include <boardmanager/include/boardmodel.hpp>
#include <lib/scene/include/renderizable.hpp>
#include <lib/time/include/timercomponent.hpp>
#include <lib/scene_components/include/statescontroller.hpp>
#include <lib/scene_components/include/statescontrolleractuator.hpp>
#include <lib/time/include/timercomponent.hpp>

namespace zoper
{
class PauseSceneNode;
class GameOverSceneNode;

namespace mtps = lib;
namespace haf = lib;
namespace scene = haf::scene;

class GameScene final : public scene::Scene,
                        public haf::StatesControllerActuator<GameSceneStates>
{
public:
    GameScene();
    ~GameScene() override;

    static constexpr char StaticTypeName[] = "GameScene";

    void onCreated() override;

    void onEnterState(const GameSceneStates &) override;
    void onExitState(const GameSceneStates &) override;

    mtps::sptr<LevelProperties> levelProperties() const
    {
        return level_properties_;
    }
    
    void goGameOver();

private:
    struct GameScenePrivate;
    haf::uptr<GameScenePrivate> private_;
    using BaseClass = scene::Scene;
    void generateNextToken();
    mtps::vector2df tileSize() const;

    mtps::sptr<scene::StatesController<GameSceneStates>> m_sceneStates;
    void launchPlayer();
    void _debugDisplayBoard() const;

    mtps::sptr<BoardGroup> m_boardGroup;

    // Timer related properties
    mtps::sptr<time::TimerComponent> scene_timer_component_;
    time::TimerConnectorSPtr m_nextTokenTimer;

    // General properties.
    mtps::u8 m_nextTokenPart{0U};
    mtps::sptr<LevelProperties> level_properties_;
    mtps::sptr<GameOverSceneNode> m_gameOver;
    mtps::sptr<PauseSceneNode> pause_node_;
};
} // namespace zoper

#endif
