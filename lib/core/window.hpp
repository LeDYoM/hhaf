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

		class Window : public AppService
		{
		public:
			Window(const WindowCreationParams &wcp);
			~Window();
			bool preLoop();
			void postLoop();
			virtual void onCreate();
			virtual void onDestroy();

			const input::KeyStates &currentKeyStates() const noexcept;
			Property<Rectf32> viewPort;
			Property<Rectf32> viewRect;

			void draw(const draw::VertexArray &va, const draw::RenderStates &rs);

		private:
			void create(const WindowCreationParams &wcp);
			uptr<WindowPrivate> m_wPrivate{ nullptr };
			std::string m_title;
		};
	}
}

#endif
