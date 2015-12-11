#ifndef __LIB_PROGRAMCONTROLLER_HPP__
#define __LIB_PROGRAMCONTROLLER_HPP__

#include "../types.hpp"
#include "../compileconfig.hpp"

#include <vector>

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
		
		class ProgramController
		{
		public:

			ProgramController();
			virtual ~ProgramController();
			
			virtual void onInit()=0;
			virtual std::vector<sptr<lib::scn::Scene>> scenesVector() = 0;
			virtual std::string resourceFile() { return ""; }

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
