#include "window.hpp"
#include "config.h"
#include "log.hpp"
#include "timer.hpp"
#include "host.hpp"
#include <lib/include/iapp.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/backend/backendfactory.hpp>

namespace lib
{
	namespace core
	{
		struct Window::WindowPrivate
		{
			Timer globalClock;
			u64 lastTimeFps{ 0 };
			s32 lastFps{ 0 };
			s32 currentFps{ 0 };
			sptr<backend::IWindow> m_backendWindow;
		};

		Window::Window(const WindowCreationParams &wcp)
			: m_wPrivate{ muptr<WindowPrivate>() }, m_title{ wcp.windowTitle }
		{
			logConstruct_NOPARAMS;
			create(wcp);
		}

		Window::~Window()
		{
			logDestruct_NOPARAMS;
		}

		void Window::draw(const scene::VertexArray & va, const scene::RenderStates& rs)
		{
			m_wPrivate->m_backendWindow->draw(va, rs);
		}

		bool Window::arePendingKeyPresses() const
		{
			return m_wPrivate->m_backendWindow->arePendingKeyPresses();
		}

		bool Window::arePendingKeyReleases() const
		{
			return m_wPrivate->m_backendWindow->arePendingKeyReleases();
		}

		input::Key Window::popKeyPress()
		{
			return m_wPrivate->m_backendWindow->popKeyPress();
		}

		input::Key Window::popKeyRelease()
		{
			return m_wPrivate->m_backendWindow->popKeyRelease();
		}

		void Window::create(const WindowCreationParams &wcp)
		{
			logDebug("Going to create Window");
			logDebug("Resolution:", wcp.width, "x", wcp.height ,"x", wcp.bpp);
			logDebug("Fullscreen:" , wcp.fullScreen);
			logDebug("Antialiasing:", wcp.antialiasing);

			__ASSERT(!m_wPrivate->m_backendWindow, "Cannot create window twice");
			logDebug("Creating window...");

			// Create window object
			m_wPrivate->m_backendWindow = backend::BackendFactory::instance()->getOrCreateWindow();
			logDebug("Window created");
			logDebug("Registering for view changes...");
			backend::IWindow &bw(*m_wPrivate->m_backendWindow);

			// Create physical window
			if (const bool result{ bw.createWindow(wcp) }) {
				viewPort = bw.viewPort();
				viewRect = bw.viewRect();
				viewPort.setCallback([this]() {m_wPrivate->m_backendWindow->setViewport(viewPort()); });
				viewRect.setCallback([this]() {m_wPrivate->m_backendWindow->setViewRect(viewRect()); });
			}
			logDebug("Window creation completed");
		}

		bool Window::preLoop()
		{
			backend::IWindow &bw(*m_wPrivate->m_backendWindow);
			auto eMs = m_wPrivate->globalClock.getElapsedTime().asMilliSeconds();
			if ((eMs - m_wPrivate->lastTimeFps) > 1000) {
				m_wPrivate->lastTimeFps = eMs;
				m_wPrivate->lastFps = m_wPrivate->currentFps;
				m_wPrivate->currentFps = 0;
				str wtitle(m_title + " FPS:" + str(m_wPrivate->lastFps));
				bw.setWindowTitle(wtitle.ic_str());
			}
			++(m_wPrivate->currentFps);
			bw.clear();

			return bw.processEvents();
		}

		void Window::postLoop()
		{
			m_wPrivate->m_backendWindow->display();
		}

		void Window::onCreate()
		{
			logDebug("Window created");
		}

		void Window::onDestroy()
		{
			logDebug("Going to close Window");
			m_wPrivate->m_backendWindow->closeWindow();
			logDebug("Window closed");
		}
	}
}
