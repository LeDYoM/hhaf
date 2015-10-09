#include "programcontroller.hpp"
#include "window.hpp"
#include "scenemanager.hpp"
#include "scene.hpp"
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
			// Not really necessary, but it is better for security
			Scene::p_scnManager.reset();
			SceneManager::p_parentWindow.reset();
			LOG_DESTRUCT_NOPARAMS;
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

		void ProgramController::setWindow(sptr<Window> window)
		{
			__ASSERT(window, "window is null");
			p_window = window;
			SceneManager::p_parentWindow = window;
		}

		void ProgramController::setSceneManager(sptr<SceneManager> sceneManager)
		{
			__ASSERT(sceneManager, "");
			__ASSERT(p_window, "");
			p_sceneManager = sceneManager;
			Scene::p_scnManager = p_sceneManager;
		}
	}
}
