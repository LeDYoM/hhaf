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
	class Tile;

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
		void for_each_token_in_line(const lib::vector2du32 &startPosition, const Direction &direction,
			std::function<bool(const lib::vector2du32 &, const Direction &)> updatePredicate);

		void movePlayer(const Direction &dir);
		void launchPlayer();

		void _debugDisplayBoard() const;
		lib::sptr<lib::board::BoardModel> p_boardModel{ nullptr };
		GameData _gameData;
		sf::Clock clock;
		lib::s32 _millisBetweenTokens{ 100 };
		lib::u8 _nextTokenPart{ 0 };
		lib::sptr<Player> p_player{ nullptr };
		TokenProcessor _tokenProcessor;

		void addPlayer();
		virtual void onKeyPressed(sf::Event::KeyEvent kEvent);
		virtual void onKeyReleased(sf::Event::KeyEvent kEvent);

		// Inherited via ITilesController
		virtual void tileSet(const lib::vector2du32 &position, lib::board::WITilePointer nTile) override;
		virtual void tileMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::board::WITilePointer tile) override;

		// Specializations from ITilesController for our tokens.
		void tokenChangedValue(const lib::vector2du32 &position, lib::sptr<Tile> tile);
		void tokenMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Tile> tile);
		void tokenAppeared(const lib::vector2du32 &position, lib::sptr<Tile> tile);
		void tokenDissapeared(const lib::vector2du32 &position);

		void playerChangedValue(const lib::vector2du32 &position, lib::sptr<Player> player);
		void playerMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Player> player);
		void playerAppeared(const lib::vector2du32 &position, lib::sptr<Player> player);
		void playerDissapeared(const lib::vector2du32 &position);
	};
}

#endif
