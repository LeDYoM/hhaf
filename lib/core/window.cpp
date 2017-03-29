#include <locale>
#include "window.hpp"
#include "config.h"
#include "log.hpp"
#include "timer.hpp"
#include "host.hpp"
#include <lib/include/iapp.hpp>
#include <lib/core/inputsystem.hpp>

namespace lib
{
	namespace core
	{
		struct WindowPrivate
		{
			Timer globalClock;
			u64 lastTimeFps{ 0 };
			s32 lastFps{ 0 };
			s32 currentFps{ 0 };
			input::KeyStates m_keyStates;
		};

		Window::Window(const WindowCreationParams &wcp)
			: p_wPrivate{ new WindowPrivate() }, m_title{ wcp.windowTitle }
		{
			logConstruct_NOPARAMS;
			create(wcp);
		}

		Window::~Window()
		{
			logDestruct_NOPARAMS;
		}

		void Window::create(const WindowCreationParams &wcp)
		{
			logDebug("Going to create Window");
			logDebug("Resolution:", wcp.width, "x", wcp.height ,"x", wcp.bpp);
			logDebug("Fullscreen:" , wcp.fullScreen);
			logDebug("Antialiasing:", wcp.antialiasing);

			createWindow(wcp);

			viewPort = backend::RenderWindow::viewPort();
			viewRect = backend::RenderWindow::viewRect();
			viewPort.setCallback([this]() {backend::RenderWindow::setViewport(viewPort()); });
			viewRect.setCallback([this]() {backend::RenderWindow::setViewRect(viewRect()); });
		}

		bool Window::preLoop()
		{
			auto eMs = p_wPrivate->globalClock.getElapsedTime().asMilliSeconds();
			if ((eMs - p_wPrivate->lastTimeFps) > 1000) {
				p_wPrivate->lastTimeFps = eMs;
				p_wPrivate->lastFps = p_wPrivate->currentFps;
				p_wPrivate->currentFps = 0;
				setTitle(m_title + " FPS:" + std::to_string(p_wPrivate->lastFps));
			}
			++(p_wPrivate->currentFps);
			clear();

			return backend::RenderWindow::processEvents();
		}

		void Window::postLoop()
		{
			display();
		}

		void Window::onCreate()
		{
			logDebug("Window created");
		}

		void Window::onDestroy()
		{
			logDebug("Going to close Window");
			close();
			logDebug("Window closed");
		}

		const input::KeyStates & Window::currentKeyStates() const noexcept
		{
			return p_wPrivate->m_keyStates;
		}
	}
}
