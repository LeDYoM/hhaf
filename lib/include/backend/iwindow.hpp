#pragma once

#ifndef LIB_BACKEND_IWINDOW_INCLUDE_HPP
#define LIB_BACKEND_IWINDOW_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/vertex.hpp>
#include <lib/include/key.hpp>
#include <lib/scene/vertexarray.hpp>
#include "iinput.hpp"
#include "itexture.hpp"

namespace lib
{
	struct WindowCreationParams;
	namespace backend
	{
        class IRenderTarget;
		class IWindow : public IInput
		{
		public:

			virtual ~IWindow() {}

			virtual bool createWindow(const WindowCreationParams &wcp) = 0;
            virtual bool activate(const bool activate = true) = 0;

			virtual bool processEvents() = 0;

			virtual void display() = 0;
			virtual void setWindowTitle(str newTitle) = 0;
			virtual void closeWindow() = 0;

            virtual IRenderTarget *renderTarget() = 0;
		};

		class IWindowProviderInfo
		{
		public:
			virtual const str info() = 0;
			virtual ~IWindowProviderInfo() {}
		};

	}
}

#endif
