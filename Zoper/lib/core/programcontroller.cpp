#include "programcontroller.hpp"
#include "window.hpp"
#include "../scn/scenemanager.hpp"
#include "../scn/scene.hpp"
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
			p_window = sptr<Window>(new Window(this));

			onInit();
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
			return p_window->loopStep();
		}
	}
}
