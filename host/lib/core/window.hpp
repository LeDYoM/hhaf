#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include "renderwindow.hpp"

namespace lib
{
	struct WindowCreationParams;

	namespace core
	{
		struct WindowPrivate;
		class AppController;

		class Window : public AppService, public external::RenderWindow
		{
		public:
			Window(AppController *const appController, const WindowCreationParams &wcp);
			virtual ~Window();
			bool preLoop();
			bool postLoop();
			virtual void onCreate();
			virtual void onDestroy();
			u32 getRandomNumer(u32 max = 1, u32 min = 0);
			void exitProgram();

		private:
			void create(const WindowCreationParams &wcp);
			void keyEvent(sf::Event e);

			uptr<WindowPrivate> p_wPrivate{ nullptr };
			bool _shouldClose{ false };
			std::string _title;
		};
	}
}

#endif
