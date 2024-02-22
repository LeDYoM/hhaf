#include "glfw_render_window.hpp"
#include "conversions.hpp"
#include <string>
#include <GLFW/glfw3.h>

using namespace htps;

namespace haf::backend::glfwb
{
GLFWRenderWindow::GLFWRenderWindow() :
    m_render_window{nullptr}, m_already_created{false}
{}

GLFWRenderWindow::~GLFWRenderWindow()
{
    if (m_already_created)
    {
        glfwTerminate();
    }
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

bool GLFWRenderWindow::isAlreadyCreated() const
{
    return m_already_created;
}

bool GLFWRenderWindow::createWindow(u32 const width,
                                    u32 const height,
                                    u8 const red_bpp,
                                    u8 const green_bpp,
                                    u8 const blue_bpp,
                                    u8 const alpha_bpp,
                                    u32 const num_extra_parameters,
                                    u32 const* const extra_parameters)
{
    (void)(width);
    (void)(height);
    (void)(red_bpp);
    (void)(green_bpp);
    (void)(blue_bpp);
    (void)(alpha_bpp);
    (void)(num_extra_parameters);
    (void)(extra_parameters);
    if (!m_already_created)
    {
        m_already_created = true;
        if (glfwInit() != 0)
        {
            ParamExtractor prm_xtr{num_extra_parameters, extra_parameters};
            //    uint width = prm_xtr.getParam(800U);
            //    uint height = prm_xtr.getParam(600U);
            //    uint bpp = prm_xtr.getParam(32U);

            unsigned int w   = static_cast<unsigned int>(width);
            unsigned int h   = static_cast<unsigned int>(height);
            unsigned int bpp = static_cast<unsigned int>(red_bpp + green_bpp +
                                                         blue_bpp + alpha_bpp);

            // sf::ContextSettings context_settings = sf::ContextSettings();
            //            m_render_window = htps::muptr<GL
            m_render_window =
                glfwCreateWindow(640, 480, "My Title", NULL, NULL);

            m_render_window->create(sf::VideoMode(w, h, bpp), "", style,
                                    context_settings);

            m_render_window->setVerticalSyncEnabled(false);
            m_already_created = true;
            //        m_window_render_target.setInternalRenderTarget();
        }
        return true;
    }
    return false;
}

bool GLFWRenderWindow::processEvents()
{
    /*
    input_driver_.clearInternalInputBuffer();
    sf::Event event;
    while (m_render_window->pollEvent(event))
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
    */
    return false;
}

void GLFWRenderWindow::display()
{
    //    m_render_window->display();
}

void GLFWRenderWindow::setWindowTitle(str const& /*newTitle*/)
{
    //    m_render_window->setTitle(to_sf_type(newTitle));
}

void GLFWRenderWindow::closeWindow()
{
    //    m_render_window->close();
}

rptr<IInputDriver> GLFWRenderWindow::inputDriver()
{
    //    return &input_driver_;
    return nullptr;
}

str GLFWRenderWindow::info() const
{
    //    return make_str("name:SFMLWindow;provider:SFML;provider_version:",
    //                    SFML_VERSION_MAJOR, ".", SFML_VERSION_MINOR, ".",
    //                    SFML_VERSION_PATCH,
    //                    ";version:0;subversion:2:patch:4");
    return "";
}

str GLFWRenderWindow::settingsInfo() const
{
    /*
    sf::ContextSettings settings = m_render_window->getSettings();

    return make_str("Depth bits: ", settings.depthBits,
                    ", stencil bits: ", settings.stencilBits,
                    ", antialiasing level: ", settings.antialiasingLevel,
                    ", attribute flags: ", settings.attributeFlags,
                    ", sRGB capable: ", settings.sRgbCapable,
                    ", version: ", settings.majorVersion, ".",
                    settings.minorVersion);
                    */
    return "";
}

}  // namespace haf::backend::glfwb
