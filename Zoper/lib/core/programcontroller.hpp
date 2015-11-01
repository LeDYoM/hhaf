#ifndef __LIB_PROGRAMCONTROLLER_HPP__
#define __LIB_PROGRAMCONTROLLER_HPP__

#include "../types.hpp"
#include "../compileconfig.hpp"

namespace lib
{
	namespace scn
	{
		class SceneManager;
	}
	namespace core
	{
		class Window;
		
		class ProgramController
		{
		public:

			ProgramController();
			virtual ~ProgramController();
			
			virtual void onInit()=0;
			void start();
			int loop();
			void setWindow(sptr<Window> window);
			void setSceneManager(sptr<scn::SceneManager> sceneManager);

			inline sptr<scn::SceneManager> sceneManager() const { return p_sceneManager; }
		protected:
			bool loopStep();
		private:
			sptr<Window> p_window;
			sptr<scn::SceneManager> p_sceneManager;		
		};
	}
}

#endif
