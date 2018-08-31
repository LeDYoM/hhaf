#include "zoperprogramcontroller.hpp"
#include "menu/menuscene.hpp"
#include "gameplay/gamescene.hpp"
#include "highscores/highscoresscene.hpp"
#include "common.hpp"

#include <lib/core/host.hpp>
#include <lib/core/serializer.hpp>
#include <lib/scene/scenemanager.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	ZoperProgramController::ZoperProgramController() {}
	ZoperProgramController::~ZoperProgramController() {}

	void ZoperProgramController::onInit()
	{
        appContext().setApplicationName("Zoper");
        appContext().setApplicationVersion(1);
        appContext().setApplicationSubVersion(2);
        appContext().setApplicationPatch(2);
		gameSharedData = msptr<GameSharedData>();

		keyMapping = muptr<KeyMapping>();
		Serializer<KeyMapping> kmSerializer;
		kmSerializer.deserialize("keyboard.txt", *keyMapping);
		sceneManager().setViewRect({0,0,2000,2000});
		
        sceneManager().setSceneDirector([this](sptr<Scene> scene) -> sptr<Scene> 
        {
            if (!scene)
            {
                return sceneManager().createScene<MenuScene>();
            }
            else if (typeid(*scene) == typeid(MenuScene)) 
            {
                // Did the user selected exit?
                if (gameSharedData->exitGame) {
                    return nullptr;
                }
                return sceneManager().createScene<GameScene>();
            }
			return sceneManager().createScene<MenuScene>();
		});

        sceneManager().start();
		// Hack to test high scores
		{
//            gameData->score = 10000;
//            sceneManager().startFirstScene<HighScoresScene>();
		}

        sceneManager().startFirstScene<MenuScene>();
	}

	IAppDescriptor ZoperProgramController::getAppDescriptor() const
	{
		return IAppDescriptor
		{
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
