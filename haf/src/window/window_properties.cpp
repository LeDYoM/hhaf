#include <haf/include/window/window_properties.hpp>

using namespace htps;

namespace haf::win
{


WindowProperties::WindowProperties()
{
    // Set some defaults
    width          = 800U;
    height         = 600U;
    bits_per_red   = 8U;
    bits_per_green = 8U;
    bits_per_blue  = 8U;
    bits_per_alpha = 8U;
}

u32 WindowProperties::bitsPerPixel() const
{
    return static_cast<u32>(bits_per_red() + bits_per_green() +
                            bits_per_blue() + bits_per_alpha());
}

}  // namespace haf::win
