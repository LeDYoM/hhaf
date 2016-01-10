#ifndef __LIB_PROGRAMCONTROLLER_HPP__
#define __LIB_PROGRAMCONTROLLER_HPP__

#include "../types.hpp"
#include "../compileconfig.hpp"

#include <vector>
#include <string>

namespace lib
{
	namespace scn
	{
		class SceneManager;
		class Scene;
	}
	namespace core
	{
		class Window;

		struct WindowCreationParams
		{
			std::string windowTitle;
			u32 width{ 1024 };
			u32 height{ 768 };
			u8 bpp{ 16 };
			u32 antialiasing{ 0 };
			bool vsync{ false };
			bool fullScreen{ false };
			bool resizable{ false };
		};
		
		class ProgramController
		{
		public:

			ProgramController();
			virtual ~ProgramController();
			
			virtual void onInit()=0;
			virtual std::vector<sptr<lib::scn::Scene>> scenesVector() = 0;
			virtual std::string resourceFile() { return ""; }

			virtual const WindowCreationParams getWindowCreationParams() = 0;

			void start();
			int loop();
		protected:
			bool loopStep();
		private:
			sptr<Window> p_window;
		};
	}
}

#endif
