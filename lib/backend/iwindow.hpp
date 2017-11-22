#ifndef LIB_BACKEND_IWINDOW_HPP
#define LIB_BACKEND_IWINDOW_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/vertex.hpp>
#include <lib/include/key.hpp>
#include <lib/scene/vertexarray.hpp>
#include "itexture.hpp"

namespace lib
{
	struct WindowCreationParams;
	namespace backend
	{
		class IWindow
		{
		public:

			virtual ~IWindow() {}

			virtual bool createWindow(const WindowCreationParams &wcp) = 0;
			virtual void draw(const scene::Vertex *vertices, const u32 nVertex, const scene::PrimitiveType pType, const f32 *transform, const ITexture *texture) = 0;

			virtual void setViewport(const Rectf32 &nviewport) = 0;
			virtual Rectf32 viewPort() const = 0;
			virtual void setViewRect(const Rectf32 &nviewRect) = 0;
			virtual Rectf32 viewRect() const = 0;

			virtual bool processEvents() = 0;

			virtual void display() = 0;
			virtual void clear() = 0;
			virtual void setWindowTitle(str newTitle) = 0;
			virtual void closeWindow() = 0;

			// Input part
			virtual bool arePendingKeyPresses() const = 0;
			virtual bool arePendingKeyReleases() const = 0;

			virtual input::Key popKeyPress() = 0;
			virtual input::Key popKeyRelease() = 0;
		};

		class IWindowProviderInfo
		{
		public:
			virtual const str info() = 0;
		};

	}
}

#endif

