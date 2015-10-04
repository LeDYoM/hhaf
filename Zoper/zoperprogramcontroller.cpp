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
		setWindow(std::shared_ptr<ZoperWindow>(new ZoperWindow));
		setSceneManager(std::shared_ptr<ZoperSceneManager>(new ZoperSceneManager));
	}
}
