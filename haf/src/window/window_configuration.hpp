#ifndef HAF_WINDOW_WINDOW_CONFIGURATION_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_CONFIGURATION_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/include/data/ideserializable.hpp>
#include "system/system_configuration.hpp"

namespace haf::sys
{
struct HAF_PRIVATE WindowConfigurationData
{
    htps::u32 width{800U};
    htps::u32 height{600U};
    htps::u8 bits_per_red{8U};
    htps::u8 bits_per_green{8U};
    htps::u8 bits_per_blue{8U};
    htps::u8 bits_per_alpha{8U};

    htps::u32 bitsPerPixel() const;
};

struct HAF_PRIVATE DeserializableWindowConfigurationData
    : public data::IDeserializable
{
    static constexpr char WindowWidthStr[]        = "window_width";
    static constexpr char WindowHeightStr[]       = "window_height";
    static constexpr char WindowBitsPerRedStr[]   = "window_bpr";
    static constexpr char WindowBitsPerGreenStr[] = "window_bpg";
    static constexpr char WindowBitsPerBlueStr[]  = "window_bpb";
    static constexpr char WindowBitsPerAlphaStr[] = "window_bpa";

    bool deserialize(htps::Object const& obj)
    {
        bool result{true};
        result |= obj[WindowWidthStr].as(data.width);
        result |= obj[WindowHeightStr].as(data.height);
        result |= obj[WindowBitsPerRedStr].as(data.bits_per_red);
        result |= obj[WindowBitsPerGreenStr].as(data.bits_per_green);
        result |= obj[WindowBitsPerBlueStr].as(data.bits_per_blue);
        result |= obj[WindowBitsPerAlphaStr].as(data.bits_per_alpha);

        return result;
    }

    WindowConfigurationData data;
};

class HAF_PRIVATE WindowConfiguration
    : public SystemConfiguration<DeserializableWindowConfigurationData,
                                 WindowConfigurationData>
{
public:
    htps::u32 configuredWindowWidth() const noexcept { return data().width; }

    htps::u32 configuredWindowHeight() const noexcept { return data().height; }

    htps::vector2du32 configuredWindowSize() const noexcept
    {
        return {data().width, data().height};
    }

    htps::u8 configuredBitsPerRed() const noexcept
    {
        return data().bits_per_red;
    }

    htps::u8 configuredBitsPerGreen() const noexcept
    {
        return data().bits_per_green;
    }

    htps::u8 configuredBitsPerBlue() const noexcept
    {
        return data().bits_per_blue;
    }

    htps::u8 configuredBitsPerAlpha() const noexcept
    {
        return data().bits_per_alpha;
    }

    htps::u32 bitsPerPixel() const noexcept
    {
        return static_cast<htps::u32>(configuredBitsPerRed()) +
            static_cast<htps::u32>(configuredBitsPerGreen()) +
            static_cast<htps::u32>(configuredBitsPerBlue()) +
            static_cast<htps::u32>(configuredBitsPerAlpha());
    }
};
}  // namespace haf::sys

#endif
