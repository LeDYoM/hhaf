#include "key_conversion.hpp"
#include <GLFW/glfw3.h>

namespace haf::backend::glfwb
{
static bool toBackendKey(int const key,
                         int const start_range,
                         int const end_range,
                         IKey const start_ikey,
                         IKey& out) noexcept
{
    if (key >= start_range && key <= end_range)
    {
        out = static_cast<IKey>(
            static_cast<std::underlying_type_t<IKey>>(start_ikey) +
            (key - start_range));
        return true;
    }
    return false;
}

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

    IKey ikey;
    if (toBackendKey(key, GLFW_KEY_0, GLFW_KEY_9, IKey::Num0, ikey))
    {
        return ikey;
    }
    else if (toBackendKey(key, GLFW_KEY_A, GLFW_KEY_Z, IKey::A, ikey))
    {
        return ikey;
    }

    return IKey::Unknown;
}
}  // namespace haf::backend::glfwb
