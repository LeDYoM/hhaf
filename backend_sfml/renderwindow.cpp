#include <lib/input/include/key.hpp>

#include "renderwindow.hpp"
#include "conversions.hpp"

#include <SFML/Config.hpp>

#include <string>

namespace lib::backend::sfmlb
{
RenderWindow::RenderWindow() {}
RenderWindow::~RenderWindow() {}

class ParamExtractor
{
public:
    constexpr ParamExtractor(const unsigned int size, const unsigned int *const data)
        : size_{size}, data_{data} {}

    unsigned int getParam(const unsigned int def_param = 0U)
    {
        if (current_ < size_)
        {
            return data_[current_++];
        }
        return def_param;
    }

private:
    unsigned int current_{0U};
    const unsigned int size_;
    const unsigned int *const data_;
};

bool RenderWindow::createWindow(const unsigned int size,
    const unsigned int *const data)
{
    using uint = unsigned int;
    sf::Uint32 style{sf::Style::Default};
    //        if (wcp.fullScreen)
    //            style = sf::Style::Fullscreen;

    ParamExtractor prm_xtr{size, data};
    uint width = prm_xtr.getParam(800U);
    uint height = prm_xtr.getParam(600U);
    uint bpp = prm_xtr.getParam(32U);

    sf::Window::create(sf::VideoMode(width, height, bpp), "",
                       style);

    this->setVerticalSyncEnabled(false);
    return true;
}

sf::Vector2u RenderWindow::getSize() const
{
    return Window::getSize();
}

IRenderTarget *RenderWindow::renderTarget()
{
    return this;
}

bool RenderWindow::setActive(bool active)
{
    return sf::Window::setActive(active);
}

bool RenderWindow::processEvents()
{
    sf::Event event;
    while (pollEvent(event))
    {
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

IInputDriver *RenderWindow::inputDriver()
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
} // namespace lib::backend::sfmlb
