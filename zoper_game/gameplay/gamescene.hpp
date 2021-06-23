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
#include <haf/include/render/renderizable.hpp>
#include <haf/include/time/timercomponent.hpp>
#include <haf/include/scene_components/statescontroller.hpp>
#include <haf/include/scene_components/statescontrolleractuator.hpp>
#include <haf/include/time/timercomponent.hpp>

#include "../scene_names.hpp"

namespace zoper
{
class PauseSceneNode;
class GameOverSceneNode;
class NextToken;

class GameScene final : public haf::scene::Scene,
                        public haf::scene::StatesControllerActuator<GameSceneStates>
{
public:
    GameScene();
    ~GameScene() override;

    static constexpr char StaticTypeName[] = GAME_SCENE_NAME;

    htps::str nextSceneName() override;
    void onCreated() override;

    void onEnterState(const GameSceneStates &) override;
    void onExitState(const GameSceneStates &) override;

    htps::sptr<LevelProperties> levelProperties() const
    {
        return level_properties_;
    }
    
    void goGameOver();
    void tokenHitAnimation(htps::vector2dst const& pos);

private:
    struct GameScenePrivate;
    htps::uptr<GameScenePrivate> p_;
    using BaseClass = scene::Scene;
    void generateNextToken();
    htps::vector2df tileSize() const;

    htps::sptr<scene::StatesController<GameSceneStates>> m_sceneStates;
    void launchPlayer();
    void _debugDisplayBoard() const;
    void keyPressed(input::Key key);

    htps::sptr<BoardGroup> m_boardGroup;

    // Timer related properties
    htps::sptr<time::TimerComponent> scene_timer_component_;
    time::TimerConnectorSPtr m_nextTokenTimer;
    htps::sptr<NextToken> next_token_;

    // General properties.
    htps::u16 m_nextTokenPart{0U};
    htps::sptr<LevelProperties> level_properties_;
    htps::sptr<GameOverSceneNode> m_gameOver;
    htps::sptr<PauseSceneNode> pause_node_;
};
} // namespace zoper

#endif
