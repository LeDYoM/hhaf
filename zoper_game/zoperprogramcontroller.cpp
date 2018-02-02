#include "zoperprogramcontroller.hpp"
#include "scenes/menuscene.hpp"
#include "scenes/gamescene.hpp"
#include "scenes/highscoresscene.hpp"
#include "common.hpp"

#include <lib/core/host.hpp>
#include <lib/core/serializer.hpp>
#include <lib/scene/scenemanager.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	ZoperProgramController::ZoperProgramController() = default;
	ZoperProgramController::~ZoperProgramController() = default;

	void ZoperProgramController::onInit()
	{
		gameData = msptr<GameData>();

		keyMapping = muptr<KeyMapping>();
		Serializer<KeyMapping> kmSerializer;
		kmSerializer.deserialize("keyboard.txt", *keyMapping);
		sceneManager().setViewRect({0,0,2000,2000});
		sceneManager().setSceneDirector([this](sptr<Scene> scene) -> sptr<Scene> {
            if (typeid(*scene) == typeid(MenuScene)) {
                // Did the user selected exit?
                if (gameData->startGameData.exitGame) {
                    return nullptr;
                }
                return sceneManager().createScene<GameScene>();
            }
			return sceneManager().createScene<MenuScene>();
		});
		sceneManager().start();
		// Hack to test high scores
		{
//			gameData->score = 10000;
//			sceneManager().startFirstScene<HighScoresScene>();
		}

		sceneManager().startFirstScene<MenuScene>();
	}

	const IAppDescriptor ZoperProgramController::getAppDescriptor() const
	{
		return IAppDescriptor
		{
			"Zoper",
			1,
			1,
			4,
			"config.cfg",
			"res.cfg",
			WindowCreationParams
			{
				"ZOPER",
				1024,
				768,
				32,
				0,
				false,
				false,
				false
			}
		};
	}

	int ZoperProgramController::loop()
	{
		return 0;
	}
}
