#include "renderwindow.hpp"

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
