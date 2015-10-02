#ifndef __LIB_PROGRAMCONTROLLER_HPP__
#define __LIB_PROGRAMCONTROLLER_HPP__

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
			void setWindow(Window *window) { _window = window; }
			void setSceneManager(SceneManager *sceneManager) { _sceneManager = sceneManager; }

			inline SceneManager *sceneManager() const { return _sceneManager; }
		protected:
			void loopStep();
		private:
			Window *_window;
			SceneManager *_sceneManager;
			
		private:
			bool exit;
			
		};
	}
}

#endif
