#include <backend_client/include/backend_exporter.hpp>
#include "glfw_backend_manager.hpp"

haf::backend::glfwb::GLFWBackendManager* glfw_backend_manager{nullptr};

DEFAULT_INIT_FINISH_FUNCTIONS(glfw_backend_manager)
