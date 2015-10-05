#ifndef __LIB_PROGRAMCONTROLLER_HPP__
#define __LIB_PROGRAMCONTROLLER_HPP__

#include <memory>

namespace lib
{
	namespace core
	{
		class Window;
		class SceneManager;
		
		class ProgramController
		{
		public:
			using WindowPtr = std::shared_ptr<Window>;
			using SceneManagerPtr = std::shared_ptr<SceneManager>;

			ProgramController();
			virtual ~ProgramController();
			
			virtual void onInit()=0;
			void start();
			int loop();
			void setWindow(WindowPtr window) { p_window = window; }
			void setSceneManager(SceneManagerPtr sceneManager) { p_sceneManager = sceneManager; }

			inline std::shared_ptr<SceneManager> sceneManager() const { return p_sceneManager; }
		protected:
			bool loopStep();
		private:
			std::shared_ptr<Window> p_window;
			std::shared_ptr<SceneManager> p_sceneManager;		
		};
	}
}

#endif
