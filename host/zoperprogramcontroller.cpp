#include "zoperprogramcontroller.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"
#include "common.hpp"
#include <lib/core/host.hpp>
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

			return nullptr;
		}
	};

	ZoperProgramController::ZoperProgramController() = default;

	ZoperProgramController::~ZoperProgramController() = default;

	void ZoperProgramController::onInit()
	{
		sceneManager().viewRect = Rectf32{0,0,2000,2000};

		sceneManager().setScenesController(muptr<ScenesController>(sceneManager()));
//		sceneManager().addSceneType<GameScene>();
//		sceneManager().addSceneType<MenuScene>();

//		sceneManager().setCurrentSceneType<MenuScene>();
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