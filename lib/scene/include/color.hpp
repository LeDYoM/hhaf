#pragma once

#ifndef LIB_SCENE_COLOR_INCLUDE_HPP
#define LIB_SCENE_COLOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <algorithm>
#include <limits>

namespace lib::scene
{
namespace detail
{
template <typename value_type>
static constexpr value_type value_max = std::numeric_limits<value_type>::max();

template <typename value_type>
static constexpr value_type value_min = std::numeric_limits<value_type>::min();

template <typename Dest, typename Source>
constexpr Dest ensureLimits(Source source) noexcept
{
    return static_cast<Dest>(std::min(
        static_cast<Source>(value_max<Dest>),
        std::max(
            source,
            static_cast<Source>(value_min<Dest>))));
}

template <typename value_type>
constexpr float normalize(const value_type v) noexcept
{
    return static_cast<float>(
        static_cast<float>(v) /
        static_cast<float>(value_max<value_type>));
}

template <typename value_type>
constexpr void denormalize(const float v, value_type &d) noexcept
{
    d = static_cast<value_type>(v * value_max<value_type>);
}
} // namespace detail

template <typename value_type>
struct ColorImp
{
    static constexpr value_type value_max = detail::value_max<value_type>;
    static constexpr value_type value_min = detail::value_min<value_type>;

    template <typename Source>
    static constexpr value_type ensureLimits(Source source) noexcept
    {
        return detail::ensureLimits<value_type, Source>(std::move(source));
    }

    constexpr ColorImp() noexcept : r{}, g{}, b{}, a{value_max} {}
    constexpr ColorImp(const value_type red,
                    const value_type green,
                    const value_type blue,
                    const value_type alpha = value_max) noexcept
        : r{red}, g{green}, b{blue}, a{alpha} {}

    static constexpr ColorImp fromFloats(const float red, const float green, const float blue, const float alpha = 1.0F) noexcept
    {
        return ColorImp{static_cast<value_type>(red * value_max),
                     static_cast<value_type>(green * value_max),
                     static_cast<value_type>(blue * value_max),
                     static_cast<value_type>(alpha * value_max)};
    }

    template <typename = std::enable_if_t<std::is_same_v<value_type, u8>>>
    constexpr explicit ColorImp(const u32 color) noexcept
        : r{static_cast<value_type>((color & 0xff000000) >> 24U)},
          g{static_cast<value_type>((color & 0x00ff0000) >> 16U)},
          b{static_cast<value_type>((color & 0x0000ff00) >> 8U)},
          a{static_cast<value_type>((color & 0x000000ff) >> 0U)} {}

    template <typename = std::enable_if_t<std::is_same_v<value_type, u8>>>
    constexpr u32 toInteger() const noexcept { return (r << 24U) | (g << 16U) | (b << 8U) | a; }

    constexpr ColorImp(const ColorImp &) noexcept = default;
    constexpr ColorImp &operator=(const ColorImp &) noexcept = default;
    constexpr ColorImp(ColorImp &&) noexcept = default;
    constexpr ColorImp &operator=(ColorImp &&) noexcept = default;

    template <typename vt>
    constexpr ColorImp(const ColorImp<vt> &other) noexcept
    {
        r = ensureLimits(static_cast<value_type>(other.r));
        g = ensureLimits(static_cast<value_type>(other.g));
        b = ensureLimits(static_cast<value_type>(other.b));
        a = ensureLimits(static_cast<value_type>(other.a));
    }

    template <typename vt>
    constexpr ColorImp& operator=(const ColorImp<vt> &other) noexcept
    {
        r = ensureLimits(static_cast<value_type>(other.r));
        g = ensureLimits(static_cast<value_type>(other.g));
        b = ensureLimits(static_cast<value_type>(other.b));
        a = ensureLimits(static_cast<value_type>(other.a));
    }

    constexpr bool operator==(const ColorImp &right) const noexcept
    {
        return (r == right.r && g == right.g && b == right.b && a == right.a);
    }

    constexpr bool operator!=(const ColorImp &right) const noexcept
    { 
        return !(*this == right);
    }

    template <typename vt>
    constexpr ColorImp operator+(const ColorImp<vt> &right) const noexcept
    {
        return (ColorImp(*this) += right);
    }

    constexpr ColorImp operator-(const ColorImp &right) const noexcept
    {
        return (ColorImp(*this) -= right);
    }

    constexpr ColorImp operator*(const ColorImp &right) const noexcept
    {
        return (ColorImp(*this) *= right);
    }

    template <typename vt>
    constexpr ColorImp &operator+=(const ColorImp<vt> &right) noexcept
    {
        r = ensureLimits(static_cast<vt>(r) + right.r);
        g = ensureLimits(static_cast<vt>(g) + right.g);
        b = ensureLimits(static_cast<vt>(b) + right.b);
        a = ensureLimits(static_cast<vt>(a) + right.a);
        return *this;
    }

    constexpr ColorImp &operator-=(const ColorImp &right) noexcept
    {
        r = ensureLimits(static_cast<s32>(r) - right.r);
        g = ensureLimits(static_cast<s32>(g) - right.g);
        b = ensureLimits(static_cast<s32>(b) - right.b);
        a = ensureLimits(static_cast<s32>(a) - right.a);
        return *this;
    }

    constexpr ColorImp &operator*=(const ColorImp &right) noexcept
    {
        r = static_cast<value_type>(static_cast<u32>(r) * right.r / value_max);
        g = static_cast<value_type>(static_cast<u32>(g) * right.g / value_max);
        b = static_cast<value_type>(static_cast<u32>(b) * right.b / value_max);
        a = static_cast<value_type>(static_cast<u32>(a) * right.a / value_max);
        return *this;
    }

    constexpr ColorImp &operator*=(const f32 delta) noexcept
    {
        r = detail::ensureLimits<value_type>(static_cast<f32>(r) * delta);
        g = detail::ensureLimits<value_type>(static_cast<f32>(g) * delta);
        b = detail::ensureLimits<value_type>(static_cast<f32>(b) * delta);
        a = detail::ensureLimits<value_type>(static_cast<f32>(a) * delta);
        return *this;
    }

    constexpr ColorImp &operator/=(const f32 delta) noexcept
    {
        r = detail::ensureLimits<value_type>(static_cast<f32>(r) / delta);
        g = detail::ensureLimits<value_type>(static_cast<f32>(g) / delta);
        b = detail::ensureLimits<value_type>(static_cast<f32>(b) / delta);
        a = detail::ensureLimits<value_type>(static_cast<f32>(a) / delta);
        return *this;
    }

    constexpr float red() const noexcept { return detail::normalize(r); }
    constexpr float green() const noexcept { return detail::normalize(g); }
    constexpr float blue() const noexcept { return detail::normalize(b); }
    constexpr float alpha() const noexcept { return detail::normalize(a); }

    constexpr void setRed(const f32 red) noexcept { detail::denormalize(red, r); }
    constexpr void setGreen(const f32 green) noexcept { detail::denormalize(green, g); }
    constexpr void setBlue(const f32 blue) noexcept { detail::denormalize(blue, b); }
    constexpr void setAlpha(const f32 alpha) noexcept { detail::denormalize(alpha, a); }

    value_type r;
    value_type g;
    value_type b;
    value_type a;
};

template <typename vt>
constexpr ColorImp<vt> operator*(ColorImp<vt> color, const f32 delta) noexcept
{
    return ColorImp<vt>{std::move(color)} *= delta;
}

template <typename vt>
constexpr ColorImp<vt> operator*(const f32 delta, ColorImp<vt> color) noexcept
{
    return std::move(color) * delta;
}

template <typename vt>
constexpr ColorImp<vt> operator/(ColorImp<vt> color, const f32 delta) noexcept
{
    return ColorImp<vt>{std::move(color)} /= delta;
}
template <typename vt>
constexpr ColorImp<vt> operator/(const f32 delta, ColorImp<vt> color) noexcept
{
    return std::move(color) / delta;
}

using Color = ColorImp<u8>;

namespace colors
{
static constexpr const Color Black{Color::value_min, Color::value_min, Color::value_min};
static constexpr const Color White{Color::value_max, Color::value_max, Color::value_max};
static constexpr const Color Red{Color::value_max, Color::value_min, Color::value_min};
static constexpr const Color Green{Color::value_min, Color::value_max, Color::value_min};
static constexpr const Color Blue{Color::value_min, Color::value_min, Color::value_max};
static constexpr const Color Yellow{Color::value_max, Color::value_max, Color::value_min};
static constexpr const Color Magenta{Color::value_max, Color::value_min, Color::value_max};
static constexpr const Color Cyan{Color::value_min, Color::value_max, Color::value_max};
static constexpr const Color Transparent{Color::value_min, Color::value_min, Color::value_min, Color::value_min};
} // namespace colors

} // namespace lib::scene

#endif
