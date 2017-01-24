#include "renderwindow.hpp"

namespace lib
{
	namespace core
	{
		namespace external
		{
			RenderWindow::RenderWindow() = default;

			RenderWindow::RenderWindow(sf::VideoMode mode, const std::string& title, sf::Uint32 style, const sf::ContextSettings& settings)
			{
				create(mode, title, style, settings);
			}

			RenderWindow::RenderWindow(sf::WindowHandle handle, const sf::ContextSettings& settings)
			{
				create(handle, settings);
			}

			RenderWindow::~RenderWindow() = default;

			sf::Vector2u RenderWindow::getSize() const
			{
				return Window::getSize();
			}

			void RenderWindow::onCreate()
			{
				RenderTarget::initialize();
			}

			void RenderWindow::onResize()
			{
				setView(getView());
			}
		}
	}
}
