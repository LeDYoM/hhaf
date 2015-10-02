#ifndef __LIB_PROGRAMCONTROLLER_HPP__
#define __LIB_PROGRAMCONTROLLER_HPP__

namespace lib
{
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
		protected:
			void loopStep();
			Window *_window;
			
		private:
			bool exit;
			
		};
	}
}

#endif
