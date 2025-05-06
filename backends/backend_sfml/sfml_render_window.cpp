#include "sfml_render_window.hpp"
#include "conversions.hpp"
#include "param_extractor.hpp"
#include <string>
#include <SFML/Config.hpp>

#include <SFML/Window.hpp>

#ifdef HAF_USE_SFML_IMGUI
#include <SFML/Graphics/RenderWindow.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#endif

using namespace htps;

namespace haf::backend::sfmlb
{
SFMLRenderWindow::SFMLRenderWindow() :
    m_render_window{muptr<decltype(m_render_window)::type>()}
{}

SFMLRenderWindow::~SFMLRenderWindow()
{
    m_render_window->close();
}

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

#ifdef HAF_USE_SFML_IMGUI
        ImGui::SFML::Init(*m_render_window);
#endif

        already_created_ = true;
        return true;
    }
    return false;
}

bool SFMLRenderWindow::processEvents()
{
    input_driver_.clearInternalInputBuffer();
    sf::Event event;
    while (m_render_window->pollEvent(event))
    {
#ifdef HAF_USE_SFML_IMGUI
        ImGui::SFML::ProcessEvent(*m_render_window, event);
#endif

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
    m_render_window->display();
}

void SFMLRenderWindow::setWindowTitle(str const& newTitle)
{
    m_render_window->setTitle(to_sf_type(newTitle));
}

void SFMLRenderWindow::closeWindow()
{
    m_render_window->close();
#ifdef HAF_USE_SFML_IMGUI
    ImGui::SFML::Shutdown();
#endif
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
