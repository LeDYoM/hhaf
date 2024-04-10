#ifndef HAF_BACKEND_GLFWB_KEY_CONVERSION_INCLUDE_HPP
#define HAF_BACKEND_GLFWB_KEY_CONVERSION_INCLUDE_HPP

#include <backend_dev/include/ikey.hpp>

namespace haf::backend::glfwb
{
IKey toBackendKey(int const key) noexcept;

}  // namespace haf::backend::glfwb

#endif
