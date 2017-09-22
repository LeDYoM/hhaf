#include "zoperprogramcontroller.hpp"
#include "scenes/menuscene.hpp"
#include "scenes/gamescene.hpp"
#include "scenes/highscoresscene.hpp"
#include "common.hpp"

#include <lib/core/host.hpp>
#include <lib/core/serializer.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/scene/iscenescontroller.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	class ScenesController : public IScenesController
	{
		using IScenesController::IScenesController;

		sptr<Scene> startScene() override
		{
			return msptr<MenuScene>();
		}

		sptr<Scene> scenedFinished(sptr<Scene> sceneTerminated) override
		{
			if (typeid(*sceneTerminated)==typeid(MenuScene)) {
				return msptr<GameScene>();
			}
			else if (typeid(*sceneTerminated) == typeid(GameScene)) {
				return msptr<MenuScene>();
			}

			return nullptr;
		}
	};

	ZoperProgramController::ZoperProgramController() = default;
	ZoperProgramController::~ZoperProgramController() = default;

	void ZoperProgramController::onInit()
	{
		gameData = msptr<GameData>();

		keyMapping = muptr<KeyMapping>();
		Serializer<KeyMapping> kmSerializer;
		kmSerializer.deserialize("keyboard.txt", *keyMapping);
		sceneManager().setViewRect({0,0,2000,2000});
		sceneManager().setScenesController(muptr<ScenesController>(sceneManager()));
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