#pragma once

#ifndef ZOOPER_GAMESCENE_INCLUDE_HPP__
#define ZOOPER_GAMESCENE_INCLUDE_HPP__

#include "../keymapping.hpp"
#include "../gameplay/direction.hpp"
#include "../gameplay/levelproperties.hpp"
#include "../gameshareddata.hpp"
#include "../gameplay/boardgroup.hpp"
#include "../gameplay/tokenzones.hpp"
#include "../loaders/gameresources.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/scene.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/board/boardmodel.hpp>
#include <lib/scene/nodes/textquad.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/scene/components/timercomponent.hpp>
#include <lib/scene/components/statescontroller.hpp>
#include <lib/scene/components/timercomponent.hpp>

namespace zoper
{
    class Player;
    class Tile;

    using namespace lib;

    class GameScene final : public scene::Scene, public scene::StatesControllerActuator<size_type>
    {
    public:
        GameScene();
        ~GameScene();

        // Inherited via Scene
        virtual void onCreated() override;
        virtual void updateScene();

        void onEnterState(const size_type&) override;
        void onExitState(const size_type&) override;

    private:
        using BaseClass = scene::Scene;
        void setLevel(const u32 nv);
        void updateLevelData();
        void updateGoals();
        void increaseScore(u32 scoreIncrement);
        void generateNextToken();
        void addNewToken(const vector2dst &pos, u32 newToken);
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
        void tilesCreated();
        void _debugDisplayBoard() const;

        void tokenMoved(const vector2dst &source, const vector2dst &dest, sptr<Tile> tile);

        // Timer related properties
        sptr<scene::TimerComponent> m_sceneTimerComponent;
        scene::TimerConnectorSPtr m_nextTokenTimer;
        Timer m_levelTimer;
        scene::TimerConnectorSPtr m_updateLevelDataTimer;

        // General properties.
        GameResourcesLoader m_gameresources;
        sptr<board::BoardModelComponent> p_boardModel{ nullptr };
        size_type m_consumedTokens{ 0 };
        size_type m_score{ 0 };
        u8 m_nextTokenPart{ 0 };
        GameMode m_gameMode{ GameMode::Token };
        LevelProperties levelProperties;
        TokenZones m_tokenZones;
        sptr<Player> m_player{ nullptr };

        // Nodes from the scene
        sptr<scene::SceneNode> m_mainBoardrg, m_gameOverrg, m_levelrg, m_pauseSceneNode, m_gameOverText;
        sptr<scene::nodes::TextQuad> m_scoreQuad, m_goalQuad;
        sptr<scene::nodes::NodeText> m_pauseText;
		sptr<BoardGroup> m_boardGroup;
    };
}

#endif
