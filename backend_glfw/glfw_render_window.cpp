#include "glfw_render_window.hpp"
#include "key_conversion.hpp"
#include <GLFW/glfw3.h>

using namespace htps;

namespace
{
htps::vector<int> keysPressed(100U);
htps::vector<int> keysReleased(100U);

void key_callback(GLFWwindow* window,
                  int key,
                  int scancode,
                  int action,
                  int mods)
{
    (void)(window);
    (void)(key);
    (void)(scancode);
    (void)(action);
    (void)(mods);

    if (action == GLFW_PRESS)
    {
        keysPressed.push_back(key);
    }
    else if (action == GLFW_RELEASE)
    {
        keysReleased.push_back(key);
    }
}
}  // namespace

namespace haf::backend::glfwb
{
GLFWRenderWindow::GLFWRenderWindow() = default;

GLFWRenderWindow::~GLFWRenderWindow()
{
    if (m_already_created)
    {
        glfwTerminate();
    }

    keysPressed.clear();
    keysReleased.clear();
    keysPressed.shrink_to_fit();
    keysReleased.shrink_to_fit();
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

            const unsigned int w = static_cast<unsigned int>(width);
            const unsigned int h = static_cast<unsigned int>(height);
            //            const unsigned int bpp = static_cast<unsigned int>(
            //                red_bpp + green_bpp + blue_bpp + alpha_bpp);

            // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            m_render_window = glfwCreateWindow(w, h, "", NULL, NULL);
            glfwMakeContextCurrent(m_render_window);

            glfwSetKeyCallback(m_render_window, key_callback);

            //            m_render_window->create(sf::VideoMode(w, h, bpp), "",
            //            style,
            //                                    context_settings);

            //            m_render_window->setVerticalSyncEnabled(false);
            m_already_created = true;
            //        m_window_render_target.setInternalRenderTarget();
        }
        return true;
    }
    return false;
}

void GLFWRenderWindow::processEvents(
    IWindowMessagesReceiver& iw_messages_receiver)
{
    glfwPollEvents();

    iw_messages_receiver.startInputKeysUpdate();
    for (auto const key : keysPressed)
    {
        iw_messages_receiver.keyPressed(toBackendKey(key));
    }
    keysPressed.clear();

    for (auto const key : keysReleased)
    {
        iw_messages_receiver.keyPressed(toBackendKey(key));
    }
    keysReleased.clear();

    iw_messages_receiver.endInputKeysUpdate();

    if(glfwWindowShouldClose(m_render_window))
    {
        iw_messages_receiver.requestExit();
    }
}

void GLFWRenderWindow::display()
{
    glfwSwapBuffers(m_render_window);
}

void GLFWRenderWindow::setWindowTitle(str const& newTitle)
{
    glfwSetWindowTitle(m_render_window, newTitle.c_str());
}

void GLFWRenderWindow::closeWindow()
{
    //    m_render_window->close();
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
