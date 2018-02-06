#pragma once

#ifndef ZOOPER_GAMESCENE_INCLUDE_HPP__
#define ZOOPER_GAMESCENE_INCLUDE_HPP__

#include "../keymapping.hpp"
#include "../direction.hpp"
#include "../levelproperties.hpp"
#include "../gamedata.hpp"
#include "../loaders/gameresources.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <lib/core/timer.hpp>
#include <lib/scene/scene.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/board/boardmodel.hpp>
#include <lib/scene/nodes/textquad.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/nodequad.hpp>

#include <array>

using namespace lib;

namespace zoper
{
    class Player;
    class Tile;

    class GameScene final : public scene::Scene
    {
    public:
        GameScene();
        ~GameScene();

        // Inherited via Scene
        virtual void onCreated() override;

        virtual void updateScene();

    private:
        using BaseClass = scene::Scene;
        void setLevel(const u32 nv);
        void updateLevelData();
        void updateGoals();
        void increaseScore(u32 scoreIncrement);
        void generateNextToken();
        void addNewToken(const vector2dst &pos, lib::u32 newToken);
        bool pointInCenter(const vector2dst &tPosition) const;
        vector2df board2SceneFactor() const;
        vector2df board2Scene(const lib::vector2dst &bPosition) const;
        vector2df tileSize() const;
        void for_each_token_in_line(const vector2dst &startPosition, const Direction &direction,
            function<bool(const vector2dst &, const Direction &)> updatePredicate);

        enum
        {
            Playing = 0,
            GameOver = 1,
            Pause = 2
        } _sceneStates{ Playing };

        void startGameOver();

        void launchPlayer();
        bool switchPause();

        void _debugDisplayBoard() const;

        void addPlayer();
        void tilesCreated();

        void registerEvents();

        void tileAdded(const vector2dst &position, board::SITilePointer nTile);
        void tileDeleted(const vector2dst &position, board::SITilePointer nTile);
        void tileMoved(const vector2dst &source, const vector2dst &dest, board::SITilePointer tile);

        void tileChanged(const vector2dst &position, board::SITilePointer nTile,
            const board::BoardTileData &ov, const board::BoardTileData &nv);

        void tokenMoved(const vector2dst &source, const vector2dst &dest, sptr<Tile> tile);

        // Properties
        GameResourcesLoader m_gameresources;
        PausableTimer m_gameClock;
        sptr<board::BoardModelComponent> p_boardModel{ nullptr };
        sptr<GameData> m_gameData{ nullptr };
        u8 m_nextTokenPart{ 0 };
        scene::SceneNodeSPtr m_mainBoardrg, m_gameOverrg, m_levelrg, m_pauseSceneNode, m_gameOverText;
        LevelProperties levelProperties;

        // Nodes from the scene
        sptr<Player> p_player{ nullptr };
        sptr<scene::nodes::TextQuad> m_scoreQuad, m_goalQuad;
        sptr<scene::nodes::NodeText> m_pauseText;
        vector<vector<sptr<scene::nodes::NodeQuad>>> m_backgroundTiles;
    };
}

#endif
