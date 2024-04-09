#include "sfml_render_window.hpp"

#include <SFML/Config.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLRenderWindow::SFMLRenderWindow() : m_render_window{muptr<sf::Window>()}
{}

SFMLRenderWindow::~SFMLRenderWindow()
{
    m_render_window->close();
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
        m_render_window->create(sf::VideoMode(w, h, bpp), "", style,
                                context_settings);

        m_render_window->setVerticalSyncEnabled(false);
        already_created_ = true;
        //        m_window_render_target.setInternalRenderTarget();
        return true;
    }
    return false;
}

namespace
{
constexpr IKey toBackendKey(sf::Keyboard::Key const& k) noexcept
{
    return static_cast<IKey>(k);
}
}  // namespace

void SFMLRenderWindow::processEvents(
    IWindowMessagesReceiver& iw_messages_receiver)
{
    iw_messages_receiver.startInputKeysUpdate();
    sf::Event event;
    while (m_render_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            iw_messages_receiver.requestExit();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            iw_messages_receiver.keyPressed(toBackendKey(event.key.code));
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            iw_messages_receiver.keyReleased(toBackendKey(event.key.code));
        }
    }
    iw_messages_receiver.endInputKeysUpdate();
}

void SFMLRenderWindow::display()
{
    m_render_window->display();
}

void SFMLRenderWindow::setWindowTitle(str const& newTitle)
{
    m_render_window->setTitle(newTitle.c_str());
}

void SFMLRenderWindow::closeWindow()
{
    m_render_window->close();
}

str SFMLRenderWindow::info() const
{
    return make_str("name:SFMLWindow;provider:SFML;provider_version:",
                    SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".",
                    SFML_VERSION_PATCH, ";version:0;subversion:2:patch:4");
}

str SFMLRenderWindow::settingsInfo() const
{
    sf::ContextSettings settings = m_render_window->getSettings();

    return make_str("Depth bits: ", settings.depthBits,
                    ", stencil bits: ", settings.stencilBits,
                    ", antialiasing level: ", settings.antialiasingLevel,
                    ", attribute flags: ", settings.attributeFlags,
                    ", sRGB capable: ", settings.sRgbCapable,
                    ", version: ", settings.majorVersion, ".",
                    settings.minorVersion);
}

}  // namespace haf::backend::sfmlb
