#ifndef LIB_BACKEND_IWINDOW_HPP
#define LIB_BACKEND_IWINDOW_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/include/rect.hpp>

namespace lib
{
	struct WindowCreationParams;
	namespace draw
	{
		class VertexArray;
		class RenderStatesStack;
	}
	namespace backend
	{
		class IWindow
		{
		public:

			virtual ~IWindow() {}

			virtual bool createWindow(const WindowCreationParams &wcp) = 0;
			virtual void draw(const draw::VertexArray &vertices, const draw::RenderStatesStack& states) = 0;

			virtual void setViewport(const Rectf32 &nviewport) = 0;
			virtual Rectf32 viewPort() const = 0;
			virtual void setViewRect(const Rectf32 &nviewRect) = 0;
			virtual Rectf32 viewRect() const = 0;

			virtual bool processEvents() = 0;

			virtual void display() = 0;
			virtual void clear() = 0;
			virtual void setWindowTitle(const str newTitle) = 0;
			virtual void closeWindow() = 0;
		};

		class IWindowProviderInfo
		{
		public:
			virtual const char *const info() = 0;
		};
	}
}
#endif

