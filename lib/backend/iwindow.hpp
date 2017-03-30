#ifndef LIB_BACKEND_IWINDOW_HPP
#define LIB_BACKEND_IWINDOW_HPP

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/include/rect.hpp>
#include <lib/draw/vertexarray.hpp>
#include <lib/draw/renderstates.hpp>
#include <lib/include/iapp.hpp>

namespace lib
{
	namespace backend
	{
		class IWindow
		{
		public:

			virtual ~IWindow() {}

			virtual bool createWindow(const WindowCreationParams &wcp) = 0;
			virtual void draw(const draw::VertexArray &vertices, const draw::RenderStates& states) = 0;

			virtual void setViewport(const Rectf32 &nviewport) = 0;
			virtual Rectf32 viewPort() const = 0;
			virtual void setViewRect(const Rectf32 &nviewRect) = 0;
			virtual Rectf32 viewRect() const = 0;

			virtual bool processEvents() = 0;
		};
	}
}
#endif

