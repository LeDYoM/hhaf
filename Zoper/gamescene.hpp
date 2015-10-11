#ifndef __GAMESCENE_HPP__
#define __GAMESCENE_HPP__

#include "lib/core/scene.hpp"
#include "lib/types.hpp"

namespace lib
{
	namespace board
	{
		class BoardModel;
	}
}
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
	};
	class GameScene : public lib::core::Scene
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
		bool pointInBounds(lib::u32 x, lib::u32 y) const;
		lib::sptr<lib::board::BoardModel> p_boardModel{ nullptr };
		GameData _gameData;
		sf::Clock clock;
		lib::s32 _millisBetweenTokens{ 1000 };
		lib::u8 _nextTokenPart{ 0 };

	};
}

#endif
