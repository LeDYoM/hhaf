#include "window.hpp"
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
		Window::Window(ProgramController *parentController) :p_wPrivate{ new WindowPrivate() }, p_parentController{ parentController }
		{
			LOG_CONSTRUCT_NOPARAMS;
			__ASSERTERROR(p_parentController, " Cannot create a Window with no parent");
			// TO DO: Read from config
			create(1024, 768, 32, "Zoper");

			// Create the scene manager
			p_sceneManager = sptr<lib::scn::SceneManager>(new lib::scn::SceneManager(this));
			p_sceneManager->addScenes(p_parentController->scenesVector());

		}

		Window::~Window()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void Window::create(int w, int h, int bpp, const std::string &title)
		{
			LOG_DEBUG("Going to create Window");
			sf::Window::create(VideoMode(w, h, bpp), title);
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

			clear();

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
			return false;
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

	}
}
