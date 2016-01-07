#include "window.hpp"
#include "../compileconfig.hpp"
#include "../log.hpp"
#include "../randomizer.hpp"
#include "../scn/scenemanager.hpp"
#include "programcontroller.hpp"
#include <SFML/System.hpp>

using namespace sf;

namespace lib
{
	namespace core
	{
		struct WindowPrivate
		{
			Clock globalClock;
			Int32 lastTimeFps{ 0 };
			int lastFps{ 0 };
			int currentFps{ 0 };
			Randomizer randomizer;
		};
		Window::Window(ProgramController *parentController, const WindowCreationParams &wcp)
			: p_wPrivate{ new WindowPrivate() }, p_parentController{ parentController }, _title(wcp.windowTitle)
		{
			LOG_CONSTRUCT_NOPARAMS;
			__ASSERT(p_parentController, "Cannot create a Window with no parent");
			create(wcp);

			// Create the scene manager
			p_sceneManager = sptr<lib::scn::SceneManager>(new lib::scn::SceneManager(this, p_parentController->resourceFile()));
			p_sceneManager->addScenes(p_parentController->scenesVector());
		}

		Window::~Window()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void Window::create(const WindowCreationParams &wcp)
		{
			LOG_DEBUG("Going to create Window");
			LOG_DEBUG("Resolution:" << wcp.width << "x" << wcp.height << "x" << wcp.bpp);
			LOG_DEBUG("Fullscreen:" << wcp.fullScreen);
			LOG_DEBUG("Antialiasing:" << wcp.antialiasing);

			sf::Uint32 style{ sf::Style::Titlebar | sf::Style::Close };
			if (wcp.fullScreen)
				style = sf::Style::Fullscreen;
			sf::Window::create(VideoMode(wcp.width, wcp.height, wcp.bpp), _title, style,sf::ContextSettings(0,0,wcp.antialiasing));

//			if (wcp.)
			this->setVerticalSyncEnabled(true);
			//#endif

		}

		bool Window::loopStep()
		{
			auto eMs = p_wPrivate->globalClock.getElapsedTime().asMilliseconds();
			if ((eMs - p_wPrivate->lastTimeFps) > 1000)
			{
				p_wPrivate->lastTimeFps = eMs;
				p_wPrivate->lastFps = p_wPrivate->currentFps;
				p_wPrivate->currentFps = 0;
				setTitle("FPS:" + std::to_string(p_wPrivate->lastFps));
			}
			++(p_wPrivate->currentFps);
			clear(sf::Color(128,128,128));

			sf::Event event;
			while (pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					return true;
				}
				else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
				{
					keyEvent(event);
				}
			}

			p_sceneManager->update();

			display();
			return _shouldClose;
		}

		void Window::onCreate()
		{
			LOG_DEBUG("Window created");
		}

		void Window::onDestroy()
		{
			LOG_DEBUG("Going to close Window");
			close();
			LOG_DEBUG("Window closed");
		}

		u32 Window::getRandomNumer(u32 max /*= 1*/, u32 min /*= 0*/)
		{
			return p_wPrivate->randomizer.getUInt(max, min);
		}

		void Window::keyEvent(sf::Event e)
		{
			_ASSERT(e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased);

			if (e.type == sf::Event::KeyPressed)
			{
				p_sceneManager->onKeyPressed(e.key);
			}
			else
			{
				p_sceneManager->onKeyReleased(e.key);
			}
		}

		void Window::exitProgram()
		{
			_shouldClose = true;
		}

	}
}
