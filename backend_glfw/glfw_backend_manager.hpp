#ifndef HAF_BACKEND_GLFWB_BACKEND_MANAGER_INCLUDE_HPP
#define HAF_BACKEND_GLFWB_BACKEND_MANAGER_INCLUDE_HPP

#include <backend_client/include/default_backend_manager.hpp>

namespace haf::backend::glfwb
{
class GLFWBackendManager : public haf::backend::client::DefaultBackendManager
{
public:
    void create() override;
};
}  // namespace haf::backend::glfwb

#endif
