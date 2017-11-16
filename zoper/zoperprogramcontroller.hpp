#ifndef __LIB_ZOPERPROGRAMCONTROLLER_HPP__
#define __LIB_ZOPERPROGRAMCONTROLLER_HPP__

#include <lib/include/iapp.hpp>

namespace zoper
{
	using namespace lib;
	class StartGameData;
	class GameData;
	class KeyMapping;
	class MenuScene;
	class GameScene;
	class HighScoresScene;
	class ZoperProgramController : public IApp
	{
	public:
		ZoperProgramController();
		virtual ~ZoperProgramController();

		sptr<MenuScene> createMenuScene();
		sptr<GameScene> createGameScene();
		sptr<HighScoresScene> createHighScoresScene();
		void onInit() override;
		void sceneFinished() {};
		virtual const IAppDescriptor getAppDescriptor() const override;
		virtual int loop() override;

		sptr<GameData> gameData;
		uptr<KeyMapping> keyMapping;
		sptr<StartGameData> startGameData;
	};
}

#endif