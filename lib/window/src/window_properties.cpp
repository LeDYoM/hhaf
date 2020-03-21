#include "window_properties.hpp"

namespace mtps = lib;

namespace lib::win
{

void WindowProperties::onAttached()
{
    // Set some defaults
    width = 800U;
    height = 600U;
    bits_per_pixel = 32U;
}

} // namespace lib::win
