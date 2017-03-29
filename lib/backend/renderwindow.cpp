#include "renderwindow.hpp"
#include <lib/core/host.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/include/key.hpp>
#include <SFML/Window.hpp>

namespace lib
{
	namespace backend
	{
		namespace
		{
			template <typename T>
			constexpr const sf::Rect<T> fromRect(const Rect<T> &rect) { return sf::Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

			template <typename T>
			constexpr const Rect<T> toRect(const sf::Rect<T> &rect) { return Rect<T>{rect.left, rect.top, rect.width, rect.height}; }

			template <typename T>
			constexpr const sf::Vector2<T> fromVector2d(const vector2d<T> &v) { return sf::Vector2<T>{v.x, v.y}; }

			template <typename T>
			constexpr const vector2d<T> toVector2d(const sf::Vector2<T> &v) { return vector2d<T>{v.x, v.y}; }

			input::Key doCast(const sf::Keyboard::Key &k)
			{
				int temp = k;
				return static_cast<input::Key>(temp);
			}
		}
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

		void RenderWindow::draw(const draw::VertexArray & vertices, const sf::RenderStates & states)
		{
			RenderTarget::draw((const sf::Vertex*)vertices.verticesArray().data(), vertices.verticesArray().size(), static_cast<sf::PrimitiveType>(vertices.primitiveType()), states);
		}

		void RenderWindow::setViewport(const Rectf32 & nviewport)
		{
			sf::View currentView(getView());
			currentView.setViewport(fromRect(nviewport));
			setView(currentView);
		}

		Rectf32 RenderWindow::viewPort() const
		{
			sf::View currentView(getView());
			return toRect(currentView.getViewport());
		}

		void RenderWindow::setViewRect(const Rectf32 & nviewRect)
		{
			sf::View currentView(getView());
			currentView.setCenter(fromVector2d(nviewRect.center()));
			currentView.setSize(fromVector2d(nviewRect.size()));
			setView(currentView);
		}

		Rectf32 RenderWindow::viewRect() const
		{
			sf::View currentView(getView());
			return Rectf32::fromCenterAndSize(toVector2d(currentView.getCenter()), toVector2d(currentView.getSize()));
		}

		void RenderWindow::keyEvent(sf::Event e)
		{
			_ASSERT(e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased);

			if (e.type == sf::Event::KeyPressed) {
				host().inputSystem().keyPressed(doCast(e.key.code));
			}
			else {
				host().inputSystem().keyReleased(doCast(e.key.code));
			}
		}

		bool RenderWindow::processEvents()
		{
			sf::Event event;
			while (pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					return true;
				}
				else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
					keyEvent(event);
				}
			}
			return false;
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
