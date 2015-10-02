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
		auto w = new ZoperWindow();

		setWindow(w);
		setSceneManager(new ZoperSceneManager());


	}
}
