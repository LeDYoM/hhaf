#include "zoperprogramcontroller.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"

namespace zoper
{
	ZoperProgramController::ZoperProgramController()
	{
	}

	ZoperProgramController::~ZoperProgramController()
	{
	}
		
	void ZoperProgramController::onInit()
	{
		// Init configuration data
		addConfigProperty("GraphicsLevel", "4");
	}

	std::vector<lib::sptr<lib::scn::Scene>> ZoperProgramController::scenesVector()
	{
		return{ lib::sptr<lib::scn::Scene>(new MenuScene), lib::sptr<lib::scn::Scene>(new GameScene) };
	}
}
