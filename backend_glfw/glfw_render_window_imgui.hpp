#ifndef HAF_BACKEND_GLFWB_REDNERWINDOW_EXTRA_INCLUDE_HPP
#define HAF_BACKEND_GLFWB_REDNERWINDOW_EXTRA_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>

#include <backend_dev/include/iwindow.hpp>
#include <backend_dev/include/iwindow_messages_receiver.hpp>

struct GLFWwindow;

namespace haf::backend::glfwb
{
void init(GLFWwindow* window);
void newFrame();

}  // namespace haf::backend::glfwb

#endif
