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
        case GLFW_KEY_APOSTROPHE:
            return IKey::Quote;
            break;
        case GLFW_KEY_COMMA:
            return IKey::Comma;
            break;
        case GLFW_KEY_MINUS:
            return IKey::Dash;
            break;
        case GLFW_KEY_PERIOD:
            return IKey::Period;
            break;
        case GLFW_KEY_SLASH:
            return IKey::Slash;
            break;
        case GLFW_KEY_SEMICOLON:
            return IKey::SemiColon;
            break;
        case GLFW_KEY_EQUAL:
            return IKey::Equal;
            break;
        case GLFW_KEY_LEFT_BRACKET:
            return IKey::LBracket;
            break;
        case GLFW_KEY_BACKSLASH:
            return IKey::BackSlash;
            break;
        case GLFW_KEY_RIGHT_BRACKET:
            return IKey::RBracket;
            break;
        case GLFW_KEY_GRAVE_ACCENT:
            return IKey::RBracket;
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
