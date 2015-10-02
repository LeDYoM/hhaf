#include "programcontroller.hpp"

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
		}

	}
}
