#ifndef __LIB_PROGRAMCONTROLLER_HPP__
#define __LIB_PROGRAMCONTROLLER_HPP__

#include "../types.hpp"
#include "../compileconfig.hpp"

namespace lib
{
	namespace core
	{
		class Window;
		class SceneManager;
		
		class ProgramController
		{
		public:

			ProgramController();
			virtual ~ProgramController();
			
			virtual void onInit()=0;
			void start();
			int loop();
			void setWindow(sptr<Window> window);
			void setSceneManager(sptr<SceneManager> sceneManager);

			inline sptr<SceneManager> sceneManager() const { return p_sceneManager; }
		protected:
			bool loopStep();
		private:
			sptr<Window> p_window;
			sptr<SceneManager> p_sceneManager;		
		};
	}
}

#endif
