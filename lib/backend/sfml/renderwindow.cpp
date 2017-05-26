#include "renderwindow.hpp"
#include <lib/core/host.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/include/key.hpp>
#include "conversions.hpp"
#include <lib/core/log.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>

namespace lib
{
	namespace backend
	{
		namespace sfmlb
		{
			RenderWindow::~RenderWindow() = default;

			bool RenderWindow::createWindow(const WindowCreationParams & wcp)
			{
				sf::Uint32 style{ sf::Style::Titlebar | sf::Style::Close };
				if (wcp.fullScreen)
					style = sf::Style::Fullscreen;

				// Deal with SFML bug
				sf::Window::create(sf::VideoMode(wcp.width, wcp.height, wcp.bpp), getAsString(wcp.windowTitle), style, sf::ContextSettings(0, 0, wcp.antialiasing));

				this->setVerticalSyncEnabled(wcp.vsync);
				return true;
			}

			sf::Vector2u RenderWindow::getSize() const
			{
				return Window::getSize();
			}

			void RenderWindow::draw(const scene::VertexArray & vertices, const scene::RenderStatesStack & states)
			{
				RenderTarget::draw((const sf::Vertex*)vertices.verticesArray().data(), vertices.verticesArray().size(),
					static_cast<sf::PrimitiveType>(vertices.primitiveType()),
					asRenderStates(states.top()));
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

			void RenderWindow::keyEvent(const sf::Event &e)
			{
				_ASSERT(e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased);

				const auto k(doCast(e.key.code));
				logDebug("Backend key event. Type: ", (int)(e.type), " Key: ", (int)(e.key.code));
				if (k != input::Key::Unknown) {
					if (e.type == sf::Event::KeyPressed) {
						host().inputSystem().keyPressed(k);
					}
					else {
						host().inputSystem().keyReleased(k);
					}
				}
				else {
					logWarning("Unknow keycode");
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

			void RenderWindow::display()
			{
				Window::display();
			}

			void RenderWindow::clear()
			{
				RenderTarget::clear();
			}

			void RenderWindow::setWindowTitle(const str newTitle)
			{
				Window::setTitle(getAsString(newTitle));
			}

			void RenderWindow::closeWindow()
			{
				Window::close();
			}

			void RenderWindow::onCreate()
			{
				RenderTarget::initialize();
			}

			void RenderWindow::onResize()
			{
				setView(getView());
			}

			const char * const WindowBackendInfo::info()
			{
				static const str info("SFML Backend: 1.0 Using SFML Version : " + std::to_string(SFML_VERSION_MAJOR)
					+ "." + std::to_string(SFML_VERSION_MINOR) + "." + std::to_string(SFML_VERSION_PATCH));

				return info.c_str();
			}
		}
	}
}
