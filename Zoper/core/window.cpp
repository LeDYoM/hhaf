#include "window.hpp"
#include "log.hpp"

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
		};
		Window::Window():p_wPrivate{new WindowPrivate()}
		{
		}

		void Window::create(int w, int h, int bpp, const std::string &title)
		{
			LOG_DEBUG("Going to create Window");
			sf::Window::create(VideoMode(w, h, bpp), title);
		}

		Window::~Window()
		{
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
			sf::Event Event;
			while (pollEvent(Event))
			{
				if (Event.type == sf::Event::Closed)
				{
					return true;
				}
			}

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
	}
}
