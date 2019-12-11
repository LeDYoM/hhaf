#pragma once

#ifndef LIB_SCENE_COLOR_INCLUDE_HPP
#define LIB_SCENE_COLOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <limits>

namespace lib::scene
{
namespace detail
{
    template<typename value_type>
    constexpr float normalize(const value_type v) noexcept
    {
        return static_cast<float>(
            static_cast<float>(v) /
            static_cast<float>(std::numeric_limits<value_type>::max()));
    }

    template<typename value_type>
    constexpr void denormalize(const float v, value_type& d) noexcept
    {
        d = static_cast<value_type>(v * std::numeric_limits<value_type>::max());
    }
}

struct Color
{
    using value_type = u8;

    constexpr Color() noexcept : r{}, g{}, b{}, a{255} {}
    constexpr Color(const u8 red, const u8 green, const u8 blue, const u8 alpha = 255) noexcept
        : r{red}, g{green}, b{blue}, a{alpha} {}

    static constexpr Color fromFloats(const float red, const float green, const float blue, const float alpha = 1.0F) noexcept
    {
        return Color{static_cast<value_type>(red * std::numeric_limits<value_type>::max()),
                     static_cast<value_type>(green * std::numeric_limits<value_type>::max()),
                     static_cast<value_type>(blue * std::numeric_limits<value_type>::max()),
                     static_cast<value_type>(alpha * std::numeric_limits<value_type>::max())};
    }

    template <typename = std::enable_if_t<std::is_same_v<value_type, u8>>>
    constexpr explicit Color(const u32 color) noexcept
        : r{static_cast<value_type>((color & 0xff000000) >> 24U)},
          g{static_cast<value_type>((color & 0x00ff0000) >> 16U)},
          b{static_cast<value_type>((color & 0x0000ff00) >> 8U)},
          a{static_cast<value_type>((color & 0x000000ff) >> 0U)} {}

    constexpr u32 toInteger() const noexcept { return (r << 24U) | (g << 16U) | (b << 8U) | a; }
    constexpr Color(const Color &) noexcept = default;
    Color &operator=(const Color &) noexcept = default;
    constexpr Color(Color &&) noexcept = default;
    Color &operator=(Color &&) noexcept = default;

    constexpr bool operator==(const Color &right) const noexcept
    {
        return (r == right.r && g == right.g && b == right.b && a == right.a);
    }

    constexpr bool operator!=(const Color &right) const noexcept { return !(*this == right); }

    constexpr Color operator+(const Color &right) const noexcept
    {
        return (Color(*this) += right);
    }

    constexpr Color operator-(const Color &right) const noexcept
    {
        return (Color(*this) -= right);
    }

    constexpr Color operator*(const Color &right) const noexcept
    {
        return (Color(*this) *= right);
    }

    constexpr Color &operator+=(const Color &right) noexcept
    {
        r = static_cast<u8>(std::min(static_cast<u32>(r) + right.r, 255u));
        g = static_cast<u8>(std::min(static_cast<u32>(g) + right.g, 255u));
        b = static_cast<u8>(std::min(static_cast<u32>(b) + right.b, 255u));
        a = static_cast<u8>(std::min(static_cast<u32>(a) + right.a, 255u));
        return *this;
    }

    constexpr Color &operator-=(const Color &right) noexcept
    {
        r = static_cast<u8>(std::max(static_cast<s32>(r) - right.r, 0));
        g = static_cast<u8>(std::max(static_cast<s32>(g) - right.g, 0));
        b = static_cast<u8>(std::max(static_cast<s32>(b) - right.b, 0));
        a = static_cast<u8>(std::max(static_cast<s32>(a) - right.a, 0));
        return *this;
    }

    constexpr Color &operator*=(const Color &right) noexcept
    {
        r = static_cast<u8>(static_cast<u32>(r) * right.r / 255);
        g = static_cast<u8>(static_cast<u32>(g) * right.g / 255);
        b = static_cast<u8>(static_cast<u32>(b) * right.b / 255);
        a = static_cast<u8>(static_cast<u32>(a) * right.a / 255);
        return *this;
    }

    constexpr Color operator*(const f32 delta) const noexcept
    {
        return Color{
            static_cast<u8>(static_cast<u32>(r) * delta),
            static_cast<u8>(static_cast<u32>(g) * delta),
            static_cast<u8>(static_cast<u32>(b) * delta),
            static_cast<u8>(static_cast<u32>(a) * delta)};
    }

    constexpr float red() const noexcept { return detail::normalize(r); }
    constexpr float green() const noexcept { return detail::normalize(g); }
    constexpr float blue() const noexcept { return detail::normalize(b); }
    constexpr float alpha() const noexcept { return detail::normalize(a); }

    constexpr void setRed(const f32 red) noexcept { detail::denormalize(red, r); }
    constexpr void setGreen(const f32 green) noexcept { detail::denormalize(green, g); }
    constexpr void setBlue(const f32 blue) noexcept { detail::denormalize(blue, b); }
    constexpr void setAlpha(const f32 alpha) noexcept { detail::denormalize(alpha, a); }

    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

static_assert(sizeof(Color) == sizeof(u32), "Color size is wrong");

namespace colors
{
static constexpr const Color Black{0U, 0U, 0U, 0U};
static constexpr const Color White{255U, 255U, 255U};
static constexpr const Color Red{255U, 0U, 0U};
static constexpr const Color Green{0U, 255U, 0U};
static constexpr const Color Blue{0U, 0U, 255U};
static constexpr const Color Yellow{255U, 255U, 0U};
static constexpr const Color Magenta{255U, 0U, 255U};
static constexpr const Color Cyan{0U, 255U, 255U};
static constexpr const Color Transparent{0U, 0U, 0U, 0U};
} // namespace colors
} // namespace lib::scene

#endif
