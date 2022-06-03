#include "sfml_render_window.hpp"
#include "sfml_render_target.hpp"
#include "conversions.hpp"
#include <string>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLRenderWindow::~SFMLRenderWindow()
{
    BaseClass::close();
}

class ParamExtractor
{
public:
    constexpr ParamExtractor(const unsigned int size,
                             const unsigned int* const data) :
        size_{size}, data_{data}
    {}

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
    const unsigned int* const data_;
};

bool SFMLRenderWindow::isAlreadyCreated() const
{
    return already_created_;
}

bool SFMLRenderWindow::createWindow(u32 const width,
                                    u32 const height,
                                    u8 const red_bpp,
                                    u8 const green_bpp,
                                    u8 const blue_bpp,
                                    u8 const alpha_bpp,
                                    u32 const num_extra_parameters,
                                    u32 const* const extra_parameters)
{
    if (!already_created_)
    {
        sf::Uint32 style{sf::Style::Default};
        //        if (wcp.fullScreen)
        //            style = sf::Style::Fullscreen;

        ParamExtractor prm_xtr{num_extra_parameters, extra_parameters};
        //    uint width = prm_xtr.getParam(800U);
        //    uint height = prm_xtr.getParam(600U);
        //    uint bpp = prm_xtr.getParam(32U);

        unsigned int w   = static_cast<unsigned int>(width);
        unsigned int h   = static_cast<unsigned int>(height);
        unsigned int bpp = static_cast<unsigned int>(red_bpp + green_bpp +
                                                     blue_bpp + alpha_bpp);

        sf::ContextSettings context_settings = sf::ContextSettings();
        BaseClass::create(sf::VideoMode(w, h, bpp), "", style,
                          context_settings);

        setVerticalSyncEnabled(false);
        already_created_ = true;
        m_render_window.setInternalRenderTarget(this);
        return true;
    }
    return false;
}

sf::Vector2u SFMLRenderWindow::getSize() const
{
    return BaseClass::getSize();
}

rptr<IRenderTarget> SFMLRenderWindow::renderTarget()
{
    return &m_render_window;
}

bool SFMLRenderWindow::setActive(bool active)
{
    return BaseClass::setActive(active);
}

bool SFMLRenderWindow::processEvents()
{
    input_driver_.clearInternalInputBuffer();
    sf::Event event;
    while (pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            return true;
        }
        else if (event.type == sf::Event::KeyPressed ||
                 event.type == sf::Event::KeyReleased)
        {
            input_driver_.keyEvent(event);
        }
    }
    return false;
}

void SFMLRenderWindow::display()
{
    BaseClass::display();
}

void SFMLRenderWindow::setWindowTitle(str const& newTitle)
{
    BaseClass::setTitle(to_sf_type(newTitle));
}

void SFMLRenderWindow::closeWindow()
{
    BaseClass::close();
}

rptr<IInputDriver> SFMLRenderWindow::inputDriver()
{
    return &input_driver_;
}

str SFMLRenderWindow::info() const
{
    return make_str("name:SFMLWindow;provider:SFML;provider_version:",
                    SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".",
                    SFML_VERSION_PATCH, ";version:0;subversion:2:patch:4");
}

str SFMLRenderWindow::settingsInfo()
{
    sf::ContextSettings settings = BaseClass::getSettings();

    return make_str("Depth bits: ", settings.depthBits,
                    ", stencil bits: ", settings.stencilBits,
                    ", antialiasing level: ", settings.antialiasingLevel,
                    ", attribute flags: ", settings.attributeFlags,
                    ", sRGB capable: ", settings.sRgbCapable,
                    ", version: ", settings.majorVersion, ".",
                    settings.minorVersion);
}

void SFMLRenderWindow::onCreate()
{
    BaseClass::onCreate();
}

void SFMLRenderWindow::onResize()
{
    BaseClass::onResize();
}

}  // namespace haf::backend::sfmlb
