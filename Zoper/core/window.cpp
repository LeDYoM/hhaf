#include "window.hpp"
#include "log.h"

using namespace sf;

namespace lib
{
	namespace core
	{
		Window::Window()
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

		void Window::loop()
		{
			while (isOpen())
			{
				sf::Event Event;
				while (pollEvent(Event))
				{
					if (Event.type == sf::Event::Closed)
					{
						onDestroy();
					}
				}
				display();
			}
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
