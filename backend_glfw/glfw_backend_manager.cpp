#include "glfw_backend_manager.hpp"
#include <backend_client/include/default_factory.hpp>

#include "glfw_render_window.hpp"
#include <GLFW/glfw3.h>

namespace haf::backend::glfwb
{
void GLFWBackendManager::create()
{
    using namespace haf::backend;
    using namespace haf::backend::client;

    createFactoryOfFactories<
        DefaultFactoryOf<IWindow, GLFWRenderWindow>>();
}

}  // namespace haf::backend::glfwb
