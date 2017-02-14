#include "zoperprogramcontroller.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"
#include "common.hpp"
#include <lib/core/host.hpp>

namespace zoper
{
	using namespace lib;

	ZoperProgramController::ZoperProgramController() = default;

	ZoperProgramController::~ZoperProgramController() = default;
		
	void ZoperProgramController::onInit()
	{
		host().setScene("MenuScene");
	}

	const IAppDescriptor ZoperProgramController::getAppDescriptor() const
	{
		return IAppDescriptor
		{
			"Zoper",
			1,
			1,
			3,
			"config.cfg",
			"res.cfg",
			WindowCreationParams
			(
				std::string("ZOPER"),
				1024,
				768,
				32,
				0,
				false,
				false,
				false
				)
		};
	}

	int ZoperProgramController::loop()
	{
		return 0;
	}

	vector_shared_pointers<lib::draw::Scene> ZoperProgramController::scenesVector()
	{
		return{ msptr<MenuScene>(), msptr<GameScene>() };
	}


}
