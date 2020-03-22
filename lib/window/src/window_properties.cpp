#include "window_properties.hpp"

namespace mtps = lib;

namespace lib::win
{

void WindowProperties::onAttached()
{
    // Set some defaults
    width = 800U;
    height = 600U;
    bits_per_red = 8U;
    bits_per_green = 8U;
    bits_per_blue = 8U;
    bits_per_alpha = 8U;
}

mtps::u32 WindowProperties::bitsPerPixel() const
{
    return static_cast<mtps::u32>(bits_per_red() + bits_per_green()
    + bits_per_blue() + bits_per_alpha());
}

} // namespace lib::win
