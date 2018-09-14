#pragma once

#ifndef ZOOPER_GAMESCENE_INCLUDE_HPP
#define ZOOPER_GAMESCENE_INCLUDE_HPP

#include "direction.hpp"
#include "levelproperties.hpp"
#include "boardgroup.hpp"
#include "tokenzones.hpp"

#include "../keymapping.hpp"
#include "../gameshareddata.hpp"
#include "../loaders/gameresources.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/scene.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/board/boardmodel.hpp>
#include <lib/scene/nodes/textquad.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/components/timercomponent.hpp>
#include <lib/scene/components/statescontroller.hpp>
#include <lib/scene/components/timercomponent.hpp>

namespace zoper
{
    class Player;
    class Tile;
    class GameSceneData;

    using namespace lib;

    class GameScene final : public scene::Scene, public scene::StatesControllerActuator<size_type>
    {
    public:
        GameScene();
        ~GameScene() override;

        // Inherited via Scene
        virtual void onCreated() override;
        void updateScene() override;

        void onEnterState(const size_type&) override;
        void onExitState(const size_type&) override;

    private:
        sptr<GameSceneData> m_data;
        using BaseClass = scene::Scene;
        void setLevel(const size_type nv);
        void increaseScore(const size_type scoreIncrement);
        void generateNextToken();
        void addNewToken(const vector2dst &pos, const size_type newToken);
        bool pointInCenter(const vector2dst &tPosition) const;
        vector2df board2SceneFactor() const;
        vector2df board2Scene(const lib::vector2dst &bPosition) const;
        vector2df tileSize() const;
        void for_each_token_in_line(const vector2dst &startPosition, const Direction &direction,
            function<bool(const vector2dst &, const Direction &)> updatePredicate);

        enum : size_type
        {
            Initialize = 0,
            Playing = 1,
            GameOver = 2,
            Pause = 3
        } _sceneStates{ Initialize };

        void importGameSharedData();
        void exportGameSharedData();
        void launchPlayer();
        void addPlayer();
        void _debugDisplayBoard() const;

        void tokenMoved(const vector2dst &source, const vector2dst &dest, sptr<Tile> tile);

        // Timer related properties
        sptr<scene::TimerComponent> m_sceneTimerComponent;
        scene::TimerConnectorSPtr m_nextTokenTimer;

        // General properties.
//        sptr<board::BoardModelComponent> p_boardModel{ nullptr };
        InGameData m_inGameData;
        u8 m_nextTokenPart{ 0 };
        sptr<LevelProperties> levelProperties;
        TokenZones m_tokenZones;
        sptr<Player> m_player{ nullptr };
    };
}

#endif
