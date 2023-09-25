#ifndef HAF_BACKEND_GLFWB_REDNERWINDOW_INCLUDE_HPP
#define HAF_BACKEND_GLFWB_REDNERWINDOW_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iinputdriver.hpp>

#include "glfw_input_driver.hpp"

namespace haf::backend::glfwb
{
class GLFWRenderWindow : public IWindow
{
public:
    GLFWRenderWindow();
    ~GLFWRenderWindow() override;

    bool createWindow(htps::u32 const width,
                      htps::u32 const height,
                      htps::u8 const red_bpp,
                      htps::u8 const green_bpp,
                      htps::u8 const blue_bpp,
                      htps::u8 const alpha_bpp,
                      htps::u32 const num_extra_parameters,
                      htps::u32 const* const extra_parameters) override;

    bool isAlreadyCreated() const override;

    bool processEvents() override;
    void display() override;
    void setWindowTitle(htps::str const& newTitle) override;
    void closeWindow() override;

    htps::rptr<IInputDriver> inputDriver() override;
    htps::str info() const override;
    htps::str settingsInfo() const override;

private:
//    htps::uptr<sf::Window> m_render_window;
    bool already_created_{false};
//    SFMLInputDriver input_driver_;
};

}  // namespace haf::backend::glfwb

#endif