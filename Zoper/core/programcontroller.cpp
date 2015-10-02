#include "programcontroller.hpp"
#include "window.hpp"

namespace lib
{
	namespace core
	{
		ProgramController::ProgramController():_window(0),exit(false)
		{
		}


		ProgramController::~ProgramController()
		{
		}
		
		void ProgramController::start()
		{
			onInit();
			_window->loop();
		}

	}
}
