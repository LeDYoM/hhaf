#include <backend_dev/include/ikey.hpp>

#include "glfw_input_driver.hpp"
#include "conversions.hpp"

namespace haf::backend::glfwb
{
GLFWInputDriver::GLFWInputDriver()  = default;
GLFWInputDriver::~GLFWInputDriver() = default;

void GLFWInputDriver::keyPressed(IKey const key)
{
    keys_pressed_.push_back(key);
}

void GLFWInputDriver::keyReleased(IKey const key)
{
    keys_released_.push_back(key);
}

void GLFWInputDriver::readKeyPressed(htps::vector<IKey>& keys_pressed) const
{
    keys_pressed = keys_pressed_;
}

void GLFWInputDriver::readKeyReleased(htps::vector<IKey>& keys_released) const
{
    keys_released = keys_released_;
}

void GLFWInputDriver::clearInternalInputBuffer()
{
    keys_pressed_.clear();
    keys_released_.clear();
}

}  // namespace haf::backend::glfwb
