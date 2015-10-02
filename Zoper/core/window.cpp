#include "window.hpp"
#include "log.h"

using namespace sf;

namespace lib
{
	namespace core
	{
		Window::Window()
		{
			LOG_DEBUG("Going to create Window");
			create(VideoMode(1024, 768, 32), title);
		}

		Window::~Window()
		{
		}

		void Window::setTitle(const std::string &title)
		{
			setTitle(title.c_str());
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
