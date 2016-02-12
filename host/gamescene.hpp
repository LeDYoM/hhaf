#ifndef __GAMESCENE_HPP__
#define __GAMESCENE_HPP__

#include <lib/include/types.hpp>
#include <lib/core/compileconfig.hpp>
#include <lib/core/configuration.hpp>
#include <lib/core/timer.hpp>
#include <lib/draw/scene.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/board/boardmodel.hpp>
#include "keymapping.hpp"
#include "direction.hpp"
#include "levelproperties.hpp"

#include <array>
#include <functional>

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
			lib::Rect zone;
			Direction direction;
			lib::u32 size;
		};

		void generateTokenZones();
		std::array<TokenZone, NUMWAYS> _tokenZones;

		lib::Timer levelClock;
		lib::u32 consumedTokens;

		enum GameModes : lib::u8
		{
			Token=0,
			Time=1,
		} _gameMode{ Token };
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

	private:
		KeyMapping _keyMapping;
		lib::Configuration _gameConfig;
		void setLevel(const lib::u32 nv);
		void updateLevelData();
		void updateGoals();
		void increaseScore(lib::u32 scoreIncrement);
		void generateNextToken();
		void addNewToken(const lib::vector2du32 &tPosition, lib::u32 newToken);
		bool pointInCenter(const lib::vector2du32 &tPosition) const;
		const lib::vector2df board2Scene(const lib::vector2du32 &bPosition) const;
		const lib::vector2df tileSize() const;
		void for_each_token_in_line(const lib::vector2du32 &startPosition, const Direction &direction,
			std::function<bool(const lib::vector2du32 &, const Direction &)> updatePredicate);

		enum
		{
			Playing = 0,
			GameOver = 1,
			Pause = 2
		} _sceneStates{ Playing };

		void startGameOver();

		void movePlayer(const Direction &dir);
		void launchPlayer();
		bool switchPause();

		void _debugDisplayBoard() const;

		void addPlayer();
		void tilesCreated();

		virtual void onKeyPressed(sf::Event::KeyEvent kEvent);
		virtual void onKeyReleased(sf::Event::KeyEvent kEvent);

		// Inherited via ITilesController
		virtual void tileAdded(const lib::vector2du32 &position, lib::board::WITilePointer nTile) override;
		virtual void tileDeleted(const lib::vector2du32 &position, lib::board::WITilePointer nTile) override;
		virtual void tileMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::board::WITilePointer tile) override;

		virtual void tileChanged(const lib::vector2du32 &position, lib::board::WITilePointer nTile,
			const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv) override;

		void updatePlayer(const lib::vector2du32 &dest, lib::sptr<Player> player_);

		// Specializations from ITilesController for our tokens.
		void tokenChangedValue(const lib::vector2du32 &position, lib::sptr<Tile> tile, 
			const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv);
		void tokenMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Tile> tile);
		void tokenAppeared(const lib::vector2du32 &position, lib::sptr<Tile> tile);
		void tokenDissapeared(const lib::vector2du32 &position, lib::sptr<Tile> tile);

		void playerChangedValue(const lib::vector2du32 &position, lib::sptr<Player> player,
			const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv);
		void playerMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Player> player);
		void playerAppeared(const lib::vector2du32 &position, lib::sptr<Player> player);
		void playerDissapeared(const lib::vector2du32 &position, lib::sptr<Player> player);

		virtual const lib::vector2df getDefaultSizeView() override;
		virtual void onAnimationStarted(lib::sptr<lib::scn::draw::anim::IAnimation> anim, lib::sptr<lib::scn::draw::Renderizable> node) override;
		virtual void onAnimationFinished(lib::sptr<lib::scn::draw::anim::IAnimation> anim, lib::sptr<lib::scn::draw::Renderizable> node) override;

		// Properties
		lib::PausableTimer gameClock;
		lib::sptr<lib::board::BoardModel> p_boardModel{ nullptr };
		GameData _gameData;
		lib::u32 _score{ 0 };
		lib::u8 _nextTokenPart{ 0 };
		lib::sptr<lib::scn::draw::RenderGroup> _mainBoardrg{ nullptr };
		lib::sptr<lib::scn::draw::RenderGroup> _gameOverrg{ nullptr };
		lib::sptr<lib::scn::draw::RenderGroup> _scorerg{ nullptr };
		lib::sptr<lib::scn::draw::RenderGroup> _levelrg{ nullptr };
		lib::sptr<lib::scn::draw::RenderGroup> _pauserg{ nullptr };
		lib::sptr<lib::scn::draw::RenderGroup> _backgroundTilesrg{ nullptr };
		const lib::u8 _scoreSize{ 5 };
		const lib::u8 _levelDataSize{ 5 };
		LevelProperties _levelProperties;

		// Nodes from the scene
		lib::sptr<Player> p_player{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _scoreText{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _scoreDisplay{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _currentLevelText{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _currentLevelDisplay{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _levelText{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _levelDisplay{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _goalText{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _goalDisplay{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _gameText{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _overText{ nullptr };
		lib::sptr<lib::scn::draw::NodeText> _pauseText{ nullptr };
		std::vector<std::vector<lib::sptr<lib::scn::draw::NodeShape>>> _backgroundTiles;
	};
}

#endif
