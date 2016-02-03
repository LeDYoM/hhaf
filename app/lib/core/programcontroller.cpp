#include "programcontroller.hpp"
#include "window.hpp"
#include <lib/draw/scenemanager.hpp>
#include <lib/draw/scene.hpp>
#include <lib/core/log.hpp>

#include <SFML/Config.hpp>

namespace lib
{
	namespace core
	{
		ProgramController::ProgramController()
		{
			LOG_CONSTRUCT_NOPARAMS;
			LOG_DEBUG("Starting system...");
			LOG_DEBUG("Compiled using SFML ver "<< SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH);
		}

		ProgramController::~ProgramController()
		{
			LOG_DESTRUCT_NOPARAMS;
		}
		
		void ProgramController::start()
		{
			p_window = sptr<Window>(new Window(this,getWindowCreationParams()));

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
