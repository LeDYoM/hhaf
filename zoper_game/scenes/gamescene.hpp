#pragma once

#ifndef ZOOPER_GAMESCENE_INCLUDE_HPP__
#define ZOOPER_GAMESCENE_INCLUDE_HPP__

#include "../keymapping.hpp"
#include "../direction.hpp"
#include "../levelproperties.hpp"
#include "../gamedata.hpp"
#include "../loaders/gameresources.hpp"
#include "../boardgroup.hpp"

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

namespace zoper
{
    using namespace lib;

    class Player;
    class Tile;

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

        void startGameOver();

        void launchPlayer();

        void _debugDisplayBoard() const;

        void addPlayer();
        void tilesCreated();

        void tokenMoved(const vector2dst &source, const vector2dst &dest, sptr<Tile> tile);

        // Properties
        scene::TimerConnectorSPtr m_nextTokenTimer;

        GameResourcesLoader m_gameresources;
        sptr<board::BoardModelComponent> p_boardModel{ nullptr };
        sptr<GameData> m_gameData{ nullptr };
        u8 m_nextTokenPart{ 0 };
        scene::SceneNodeSPtr m_mainBoardrg, m_gameOverrg, m_levelrg, m_pauseSceneNode, m_gameOverText;
        LevelProperties levelProperties;

        // Nodes from the scene
        sptr<Player> p_player{ nullptr };
        sptr<scene::nodes::TextQuad> m_scoreQuad, m_goalQuad;
        sptr<scene::nodes::NodeText> m_pauseText;
		sptr<BoardGroup> m_boardGroup;
    };
}

#endif
