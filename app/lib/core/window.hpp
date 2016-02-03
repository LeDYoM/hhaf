#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include "renderwindow.hpp"
#include <string>
#include <memory>

namespace lib
{
	namespace scn
	{
		class SceneManager;
	}
	namespace core
	{
		struct WindowPrivate;
		struct WindowCreationParams;
		class ProgramController;

		class Window : public external::RenderWindow
		{
		public:
			Window(ProgramController *parentController, const WindowCreationParams &wcp);
			virtual ~Window();
			bool loopStep();
			virtual void onCreate();
			virtual void onDestroy();
			u32 getRandomNumer(u32 max = 1, u32 min = 0);
			void exitProgram();

		private:
			void create(const WindowCreationParams &wcp);
			void keyEvent(sf::Event e);

			sptr<lib::scn::SceneManager> p_sceneManager;
			uptr<WindowPrivate> p_wPrivate{ nullptr };
			ProgramController *p_parentController;
			bool _shouldClose{ false };
			std::string _title;
		};
	}
}

#endif
