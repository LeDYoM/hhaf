#ifndef __GAMESCENE_HPP__
#define __GAMESCENE_HPP__

#include "lib/core/scene.hpp"
#include "lib/types.hpp"
#include "lib/board/itilescontroller.hpp"
#include "lib/board/boardmodel.hpp"
#include "lib/configuration.hpp"
#include "lib/types.hpp"
#include "lib/compileconfig.hpp"

#include <array>

#define NUMWAYS		4
#define NUMTOKENS	5
namespace zoper
{
	struct GameData
	{
		lib::u32 width{ 0 };
		lib::u32 height{ 0 };
		lib::u32 centerQuadx{ 0 };
		lib::u32 centerQuady{ 0 };
		lib::u32 centerQuadw{ 0 };
		lib::u32 centerQuadh{ 0 };

		struct TokenZone
		{
			// Filled statically
			lib::u32 x1, y1, x2, y2;
			bool horizontal;
			bool increment;
			inline lib::s32 distX() const { return x2 - x1; }
			inline lib::s32 distY() const { return y2 - y1; }

			// Filled dynamically
			lib::u32 size;
			lib::s32 incX, incY;
		};

		void generateTokenZones();
		std::array<TokenZone, NUMWAYS> _tokenZones;

	};
	class GameScene : public lib::core::Scene, public lib::board::ITilesController, public lib::Configuration
	{
	public:
		GameScene();
		virtual ~GameScene();

		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update();

		inline void setGameData(const GameData &gData) { _gameData = gData; }
		inline const GameData &getGameData() const { return _gameData; };
	private:
		void generateNextToken();
		bool pointInCenter(lib::s32 x, lib::s32 y) const;

		void _debugDisplayBoard() const;
		lib::sptr<lib::board::BoardModel> p_boardModel{ nullptr };
		GameData _gameData;
		sf::Clock clock;
		lib::s32 _millisBetweenTokens{ 1000 };
		lib::u8 _nextTokenPart{ 0 };


		void tileAppeared(lib::u32 x, lib::u32 y, lib::board::WITilePointer tile);
		void tileDissapeared(lib::u32 x, lib::u32 y);

		// Inherited via ITilesController
		virtual void tileSet(lib::u32 x, lib::u32 y, lib::board::WITilePointer nTile) override;
		virtual void tileMoved(lib::u32 xSource, lib::u32 ySource, lib::u32 xDest, lib::u32 yDest, lib::board::WITilePointer tile) override;

	};
}

#endif
