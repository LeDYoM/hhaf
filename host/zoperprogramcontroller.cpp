#include "zoperprogramcontroller.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"
#include "common.hpp"
#include <lib/core/host.hpp>
#include <lib/scene/scenemanager.hpp>

namespace zoper
{
	using namespace lib;

	ZoperProgramController::ZoperProgramController() = default;

	ZoperProgramController::~ZoperProgramController() = default;

	void ZoperProgramController::onInit()
	{
		sceneManager().setScene("MenuScene");
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

	vector_shared_pointers<lib::scene::Scene> ZoperProgramController::scenesVector()
	{
		return{ msptr<MenuScene>(), msptr<GameScene>() };
	}
}