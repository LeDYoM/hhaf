#include "window.hpp"
#include "config.h"
#include <mtypes/include/log.hpp>
#include "timer.hpp"
#include "host.hpp"
#include <lib/include/iapp.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/backend/backendfactory.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/renderdata.hpp>
#include <lib/scene/vertexarray.hpp>

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

		void Window::draw(const scene::RenderData & renderData)
		{
			m_wPrivate->m_backendWindow->draw(
				&(renderData.vArray.verticesArray()[0]), 
				renderData.vArray.verticesArray().size(),
				renderData.vArray.primitiveType(),
				renderData.transform.getMatrix(),
				renderData.texture ? renderData.texture->backEndTexture() : nullptr);
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
			log_debug_info("Going to create Window");
			log_debug_info("Resolution:", wcp.width, "x", wcp.height ,"x", wcp.bpp);
			log_debug_info("Fullscreen:" , wcp.fullScreen);
			log_debug_info("Antialiasing:", wcp.antialiasing);

			__ASSERT(!m_wPrivate->m_backendWindow, "Cannot create window twice");
			log_debug_info("Creating window...");

			// Create window object
			m_wPrivate->m_backendWindow = backend::BackendFactory::instance()->getOrCreateWindow();
			log_debug_info("Window created");
			log_debug_info("Registering for view changes...");
			backend::IWindow &bw(*m_wPrivate->m_backendWindow);

			// Create physical window
			if (const bool result{ bw.createWindow(wcp) }) {
				viewPort = bw.viewPort();
				viewRect = bw.viewRect();
				viewPort.setCallback([this]() {m_wPrivate->m_backendWindow->setViewport(viewPort()); });
				viewRect.setCallback([this]() {m_wPrivate->m_backendWindow->setViewRect(viewRect()); });
			}
			log_debug_info("Window creation completed");
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
				bw.setWindowTitle(wtitle);
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
			log_debug_info("Window created");
		}

		void Window::onDestroy()
		{
			log_debug_info("Going to close Window");
			m_wPrivate->m_backendWindow->closeWindow();
			log_debug_info("Window closed");
		}
	}
}
