#include "key_conversion.hpp"
#include <GLFW/glfw3.h>

namespace haf::backend::glfwb
{
IKey toBackendKey(int const key) noexcept
{
    switch (key)
    {
        case GLFW_KEY_SPACE:
            return IKey::Space;
            break;
        case GLFW_KEY_UNKNOWN:
            return IKey::Unknown;
            break;
    }

    if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
    {
        return static_cast<IKey>(
            static_cast<std::underlying_type_t<IKey>>(IKey::Num0) +
            (key - GLFW_KEY_0));
    }
    return IKey::Unknown;
}
}  // namespace haf::backend::glfwb
