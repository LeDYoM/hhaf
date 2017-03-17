#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <lib/backend/renderwindow.hpp>

namespace lib
{
	struct WindowCreationParams;

	namespace core
	{
		struct WindowPrivate;
		class AppController;

		class Window : public AppService, public backend::RenderWindow
		{
		public:
			Window(const WindowCreationParams &wcp);
			~Window();
			bool preLoop();
			void postLoop();
			virtual void onCreate() override;
			virtual void onDestroy();
			u32 getRandomNumer(u32 max = 1, u32 min = 0);

		private:
			void create(const WindowCreationParams &wcp);
			void keyEvent(sf::Event e);

			uptr<WindowPrivate> p_wPrivate{ nullptr };
			std::string m_title;
		};
	}
}

#endif
