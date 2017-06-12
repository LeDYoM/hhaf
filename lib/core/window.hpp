#ifndef __LIB_WINDOW_HPP__
#define __LIB_WINDOW_HPP__

#include <mtypes/include/types.hpp>
#include "appservice.hpp"
#include <lib/backend/iwindow.hpp>
#include <lib/include/key.hpp>
#include <lib/include/properties.hpp>

namespace lib
{
	struct WindowCreationParams;
	namespace scene
	{
		class VertexArray;
	}

	namespace core
	{
		class Window : public AppService
		{
		public:
			Window(const WindowCreationParams &wcp);
			~Window();
			bool preLoop();
			void postLoop();
			virtual void onCreate();
			virtual void onDestroy();

			Property<Rectf32> viewPort;
			Property<Rectf32> viewRect;

			void draw(const scene::VertexArray &va, const scene::RenderStates &rs);

			bool arePendingKeyPresses() const;
			bool arePendingKeyReleases() const;

			input::Key popKeyPress();
			input::Key popKeyRelease();

		private:
			void create(const WindowCreationParams &wcp);
			struct WindowPrivate;
			uptr<WindowPrivate> m_wPrivate;
			str m_title;
		};
	}
}

#endif
