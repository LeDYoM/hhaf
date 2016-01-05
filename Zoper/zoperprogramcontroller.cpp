#include "zoperprogramcontroller.hpp"
#include "menuscene.hpp"
#include "gamescene.hpp"
#include "common.hpp"

namespace zoper
{
	ZoperProgramController::ZoperProgramController()
		: Configuration("config.cfg")
	{
	}

	ZoperProgramController::~ZoperProgramController()
	{
		saveConfig();
	}
		
	void ZoperProgramController::onInit()
	{
		// Init configuration data
		addConfigInt(GraphicsLevelStr, 4);
	}

	std::vector<lib::sptr<lib::scn::Scene>> ZoperProgramController::scenesVector()
	{
		return{ lib::sptr<lib::scn::Scene>(new MenuScene), lib::sptr<lib::scn::Scene>(new GameScene) };
	}
	std::string ZoperProgramController::resourceFile()
	{
		return "res.cfg";
	}

	const lib::core::WindowCreationParams ZoperProgramController::getWindowCreationParams()
	{
		lib::core::WindowCreationParams params;
		params.windowTitle = "Zoper";
		params.width = addConfigInt(ResolutionXStr, 1024);
		params.height = addConfigInt(ResolutionYStr, 768);
		params.bpp = addConfigInt(BPPStr, 32);
		params.fullScreen = addConfigInt(FulscreenStr, 0) == 0 ? false : true;
		return params;
	}
}
