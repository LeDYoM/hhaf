#ifndef __GAMESCENE_HPP__
#define __GAMESCENE_HPP__

#include "lib/scn/scene.hpp"
#include "lib/compileconfig.hpp"
#include "lib/types.hpp"
#include "lib/board/itilescontroller.hpp"
#include "lib/board/boardmodel.hpp"
#include "lib/configuration.hpp"
#include "direction.hpp"
#include "tokenprocessor.hpp"
#include <array>

#define NUMWAYS			4
#define NUMTOKENS		5
#define PLAYER_TOKEN	NUMTOKENS

namespace zoper
{
	class Player;

	struct GameData
	{
		lib::vector2du32 size{ 0u, 0u };

		lib::Rect centerRect;

		struct TokenZone
		{
			// Filled statically
			lib::Rect zone;
			Direction direction;

			// Filled dynamically
			lib::u32 size;
//			lib::s32 incX, incY;
		};

		void generateTokenZones();
		std::array<TokenZone, NUMWAYS> _tokenZones;

	};
	class GameScene : public lib::scn::Scene, public lib::board::ITilesController, public lib::Configuration
	{
	public:
		GameScene();
		virtual ~GameScene();

		// Inherited via Scene
		virtual void onInit() override;
		virtual void onDeinit() override;

		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update();

		inline void setGameData(const GameData &gData) { _gameData = gData; }
		inline const GameData &getGameData() const { return _gameData; };

	private:
		void generateNextToken();
		void addNewToken(const lib::vector2du32 &tPosition, lib::u32 newToken);
		bool pointInCenter(const lib::vector2du32 &tPosition) const;
		const lib::vector2df board2Scene(const lib::vector2du32 &bPosition) const;
		const lib::vector2df tileSize() const;

		void movePlayer(const Direction &dir);

		void _debugDisplayBoard() const;
		lib::sptr<lib::board::BoardModel> p_boardModel{ nullptr };
		GameData _gameData;
		sf::Clock clock;
		lib::s32 _millisBetweenTokens{ 1000 };
		lib::u8 _nextTokenPart{ 0 };
		lib::sptr<Player> p_player{ nullptr };
		TokenProcessor _tokenProcessor;

		void addPlayer();
		virtual void onKeyPressed(sf::Event::KeyEvent kEvent);
		virtual void onKeyReleased(sf::Event::KeyEvent kEvent);

		void tileAppeared(const lib::vector2du32 &position, lib::board::WITilePointer tile);
		void tileDissapeared(const lib::vector2du32 &position);

		// Inherited via ITilesController
		virtual void tileSet(const lib::vector2du32 &position, lib::board::WITilePointer nTile) override;
		virtual void tileMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::board::WITilePointer tile) override;

	};
}

#endif
