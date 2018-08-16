#include <lib/include/key.hpp>

#include "renderwindow.hpp"
#include "conversions.hpp"

#include <SFML/Config.hpp>

#include <string>

namespace lib::backend::sfmlb
{
    void RenderTarget::draw(const scene::Vertex *vertices, const u32 nVertex, const scene::PrimitiveType pType, const f32 *transform, const ITexture *texture)
    {
        sf::RenderTarget::draw((const sf::Vertex*)vertices, nVertex,
            static_cast<sf::PrimitiveType>(pType),
            to_sf_type(transform,texture));
    }

    void RenderTarget::setViewPort(const Rectf32 & nviewport)
    {
        sf::View currentView(getView());
        currentView.setViewport(to_sf_type(nviewport));
        setView(currentView);
    }

    Rectf32 RenderTarget::viewPort() const
    {
        sf::View currentView(getView());
        return from_sft_type(currentView.getViewport());
    }

    void RenderTarget::setViewRect(const Rectf32 & nviewRect)
    {
        sf::View currentView(getView());
        currentView.setCenter(to_sf_type(nviewRect.center()));
        currentView.setSize(to_sf_type(nviewRect.size()));
        setView(currentView);
    }

    Rectf32 RenderTarget::viewRect() const
    {
        sf::View currentView(getView());
        return rectFromCenterAndSize(from_sf_type(currentView.getCenter()), from_sf_type(currentView.getSize()));
    }

    void RenderTarget::clear()
    {
        sf::RenderTarget::clear();
    }

    RenderWindow::RenderWindow() {}
	RenderWindow::~RenderWindow() {}

	bool RenderWindow::createWindow(const WindowCreationParams & wcp)
	{
		sf::Uint32 style{ sf::Style::Titlebar | sf::Style::Close };
		if (wcp.fullScreen)
			style = sf::Style::Fullscreen;

		// Deal with SFML bug
		sf::Window::create(sf::VideoMode(wcp.width, wcp.height, wcp.bpp), to_sf_type(wcp.windowTitle),
			style, sf::ContextSettings(0, 0, wcp.antialiasing));

		this->setVerticalSyncEnabled(wcp.vsync);
		return true;
	}

	sf::Vector2u RenderWindow::getSize() const
	{
		return Window::getSize();
	}

    IRenderTarget* RenderWindow::renderTarget()
    {
        return this;
    }

	void RenderWindow::keyEvent(const sf::Event &e)
	{
		const auto k(doCast(e.key.code));
		if (k != input::Key::Unknown) {
			if (e.type == sf::Event::KeyPressed) {
				m_keysPressed.push(k);
			}
			else if (e.type == sf::Event::KeyReleased) {
				m_keysReleased.push(k);
			}
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

	void RenderWindow::setWindowTitle(str newTitle)
	{
		Window::setTitle(to_sf_type(newTitle));
	}

	void RenderWindow::closeWindow()
	{
		Window::close();
	}

	bool RenderWindow::arePendingKeyPresses() const
	{
		return !m_keysPressed.empty();
	}

	bool RenderWindow::arePendingKeyReleases() const
	{
		return !m_keysReleased.empty();
	}

	template <typename T>
	input::Key popKey(T &container) {
		input::Key k(input::Key::Unknown);
		if (!container.empty()) {
			k = container.front();
			container.pop();
		}
		return k;
	}

	input::Key RenderWindow::popKeyPress()
	{
		return popKey(m_keysPressed);
	}

	input::Key RenderWindow::popKeyRelease()
	{
		return popKey(m_keysReleased);
	}

	void RenderWindow::onCreate()
	{
		RenderTarget::initialize();
	}

	void RenderWindow::onResize()
	{
		setView(getView());
	}

	const str WindowBackendInfo::info()
	{
        return make_str("SFML Backend: 1.0 Using SFML Version : ", SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".", SFML_VERSION_PATCH);
	}
}
