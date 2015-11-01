#include "zoperprogramcontroller.hpp"
#include "zoperwindow.hpp"
#include "zoperscenemanager.hpp"
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
		setWindow(lib::sptr<ZoperWindow>(new ZoperWindow));
		setSceneManager(lib::sptr<ZoperSceneManager>(new ZoperSceneManager));

		// Init configuration data
		addConfigProperty("GraphicsLevel", "4");
	}
}
