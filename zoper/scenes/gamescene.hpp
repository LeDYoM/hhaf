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
#include <lib/core/events/eventreceiver.hpp>
#include <lib/scene/scene.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/board/boardmodel.hpp>
#include <lib/scene/nodes/textquad.hpp>
#include <lib/scene/renderizables/nodetext.hpp>
#include <lib/scene/renderizables/nodequad.hpp>

#include <array>

namespace zoper
{
	class Player;
	class Tile;

	class GameScene final : public lib::scene::Scene
	{
	public:
		GameScene();
		~GameScene();

		// Inherited via Scene
		virtual void create() override;
		virtual void onDeinit() override;

		virtual void updateScene();

	private:
		lib::EventReceiver m_boardEventConnector;
		void setLevel(const lib::u32 nv);
		void updateLevelData();
		void updateGoals();
		void increaseScore(lib::u32 scoreIncrement);
		void generateNextToken();
		void addNewToken(const lib::vector2du32 &pos, lib::u32 newToken);
		bool pointInCenter(const lib::vector2du32 &tPosition) const;
		lib::vector2df board2SceneFactor() const;
		lib::vector2df board2Scene(const lib::vector2du32 &bPosition) const;
		lib::vector2df tileSize() const;
		void for_each_token_in_line(const lib::vector2du32 &startPosition, const Direction &direction,
			lib::function<bool(const lib::vector2du32 &, const Direction &)> updatePredicate);

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

		void tileAdded(const lib::vector2du32 &position, lib::board::SITilePointer nTile);
		void tileDeleted(const lib::vector2du32 &position, lib::board::SITilePointer nTile);
		void tileMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::board::SITilePointer tile);

		void tileChanged(const lib::vector2du32 &position, lib::board::SITilePointer nTile,
			const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv);

		void tokenMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Tile> tile);

		// Properties
		GameResourcesLoader m_gameresources;
		lib::PausableTimer m_gameClock;
		lib::sptr<lib::board::BoardModelComponent> p_boardModel{ nullptr };
		lib::sptr<GameData> m_gameData{ nullptr };
		lib::u8 m_nextTokenPart{ 0 };
		lib::scene::SceneNodeSPtr m_mainBoardrg, m_gameOverrg, m_levelrg, m_pauseSceneNode, m_gameOverText;
		LevelProperties levelProperties;

		// Nodes from the scene
		lib::sptr<Player> p_player{ nullptr };
		lib::sptr<lib::scene::nodes::TextQuad> m_scoreQuad, m_goalQuad;
		lib::sptr<lib::scene::nodes::NodeText> m_pauseText;
		lib::vector<lib::vector<lib::sptr<lib::scene::nodes::NodeQuad>>> m_backgroundTiles;
	};
}

#endif