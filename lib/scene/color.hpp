#pragma once

#ifndef LIB_SCENE_COLOR_HPP
#define LIB_SCENE_COLOR_HPP

#include <mtypes/include/types.hpp>
#include <algorithm>

namespace lib::scene
{
    struct Color
    {
        constexpr Color() noexcept : r{ }, g{ }, b{ }, a{ 255 } {}
        constexpr Color(const u8 red, const u8 green, const u8 blue, const u8 alpha = 255) noexcept
            : r{ red }, g{ green }, b{ blue }, a{ alpha } {}

        constexpr explicit Color(const u32 color) noexcept
            : r{ static_cast<u8>((color & 0xff000000) >> 24) },
            g{ static_cast<u8>((color & 0x00ff0000) >> 16) },
            b{ static_cast<u8>((color & 0x0000ff00) >> 8) },
            a{ static_cast<u8>((color & 0x000000ff) >> 0) } {}

        constexpr u32 toInteger() const noexcept { return (r << 24) | (g << 16) | (b << 8) | a; }
        constexpr Color(const Color&) noexcept = default;
        Color& operator=(const Color&) noexcept = default;
        constexpr Color(Color&&) noexcept = default;
        Color& operator=(Color&&) noexcept = default;

        constexpr bool operator ==(const Color& right) const noexcept
        {
            return (r == right.r && g == right.g && b == right.b && a == right.a);
        }

        constexpr bool operator !=(const Color& right) const noexcept { return !(*this == right); }

        constexpr Color operator+(const Color& right) const noexcept
        {
            return (Color(*this) += right);
        }

        constexpr Color operator -(const Color& right) const noexcept
        {
            return (Color(*this) -= right);
        }

        constexpr Color operator*(const Color& right) const noexcept
        {
            return (Color(*this) *= right);
        }

        constexpr Color &operator +=(const Color& right) noexcept
        {
            r = static_cast<u8>(std::min(static_cast<u32>(r)+right.r, 255u));
            g = static_cast<u8>(std::min(static_cast<u32>(g)+right.g, 255u));
            b = static_cast<u8>(std::min(static_cast<u32>(b)+right.b, 255u));
            a = static_cast<u8>(std::min(static_cast<u32>(a)+right.a, 255u));
            return *this;
        }

        constexpr Color &operator -=(const Color& right) noexcept
        {
            r = static_cast<u8>(std::max(static_cast<s32>(r) - right.r, 0));
            g = static_cast<u8>(std::max(static_cast<s32>(g) - right.g, 0));
            b = static_cast<u8>(std::max(static_cast<s32>(b) - right.b, 0));
            a = static_cast<u8>(std::max(static_cast<s32>(a) - right.a, 0));
            return *this;
        }

        constexpr Color &operator *=(const Color& right) noexcept
        {
            r = static_cast<u8>(static_cast<u32>(r)* right.r / 255);
            g = static_cast<u8>(static_cast<u32>(g)* right.g / 255);
            b = static_cast<u8>(static_cast<u32>(b)* right.b / 255);
            a =	static_cast<u8>(static_cast<u32>(a)* right.a / 255);
            return *this;
        }

        constexpr Color operator*(const f32 delta) const noexcept
        {
            return Color{
                static_cast<u8>(static_cast<u32>(r)* delta),
                static_cast<u8>(static_cast<u32>(g)* delta),
                static_cast<u8>(static_cast<u32>(b)* delta),
                static_cast<u8>(static_cast<u32>(a)* delta)
            };
        }

        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };

    static_assert(sizeof(Color) == sizeof(u32),"Color size is wrong");

    namespace colors
    {
        static constexpr const Color Black{ 0,0,0,0 };
        static constexpr const Color White{ 255, 255, 255 };
        static constexpr const Color Red{ 255, 0, 0 };
        static constexpr const Color Green{ 0, 255, 0 };
        static constexpr const Color Blue{ 0, 0, 255 };
        static constexpr const Color Yellow{ 255, 255, 0 };
        static constexpr const Color Magenta{ 255, 0, 255 };
        static constexpr const Color Cyan{ 0, 255, 255 };
        static constexpr const Color Transparent{ 0, 0, 0, 0 };
    }
}

#endif
