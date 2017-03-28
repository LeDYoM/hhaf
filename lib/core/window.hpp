#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <lib/backend/renderwindow.hpp>
#include <lib/include/key.hpp>
#include <lib/include/properties.hpp>

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

			const input::KeyStates &currentKeyStates() const noexcept;
			VirtualProperty<Rectf32> viewPort;
			VirtualProperty<Rectf32> viewRect;

		private:
			void create(const WindowCreationParams &wcp);
			void keyEvent(sf::Event e);

			uptr<WindowPrivate> p_wPrivate{ nullptr };
			std::string m_title;
		};
	}
}

#endif
