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

	bool RenderWindow::processEvents()
	{
		sf::Event event;
		while (pollEvent(event)) {
			if (event.type == sf::Event::Closed) 
            {
				return true;
			}
			else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) 
            {
                input_driver_.keyEvent(event);
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

    IInputDriver * RenderWindow::inputDriver()
    {
        return &input_driver_;
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
