#include "programcontroller.hpp"
#include "window.hpp"
#include "scenemanager.hpp"
#include "../log.hpp"

namespace lib
{
	namespace core
	{
		ProgramController::ProgramController()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}


		ProgramController::~ProgramController()
		{
			LOG_DESTRUCT_NOPARAMS;
		}
		
		void ProgramController::start()
		{
			onInit();
			__ASSERT(p_window, "");
			__ASSERT(p_sceneManager, "");
			p_sceneManager->p_parentWindow = p_window.get();
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
