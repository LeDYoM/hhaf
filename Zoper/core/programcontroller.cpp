#include "programcontroller.hpp"
#include "window.hpp"
#include "scenemanager.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{
		ProgramController::ProgramController()
		{
		}


		ProgramController::~ProgramController()
		{
		}
		
		void ProgramController::start()
		{
			onInit();
			__ASSERT(p_window, "");
			__ASSERT(p_sceneManager, "");
		}

		int ProgramController::loop()
		{
			bool exit=false;
			do 
			{
				exit = loopStep();
			} while (!exit);
			p_window->onDestroy();
			return 0;
		}

		bool ProgramController::loopStep()
		{
			p_sceneManager->update();
			return p_window->loopStep();
		}
	}
}
