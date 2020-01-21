#pragma once

#ifndef LIB_MTYPES_RECT_INCLUDE_HPP
#define LIB_MTYPES_RECT_INCLUDE_HPP

#include "types.hpp"
#include "vector2d.hpp"

namespace lib
{
    template <typename T>
    struct Rect
    {
        T left{}, top{}, width{}, height{};

        constexpr Rect() noexcept = default;
        constexpr Rect(const T rectLeft, const T rectTop, const T rectWidth, const T rectHeight) noexcept : left{ rectLeft }, top{ rectTop }, width{ rectWidth }, height{ rectHeight } { }
        constexpr Rect(const vector2d<T> &position, const vector2d<T> &size) noexcept : Rect{ position.x, position.y, size.x, size.y } {}
        constexpr Rect(const vector2d<T> &position, T sizeX, T sizeY) noexcept : Rect{ position.x, position.y, sizeX, sizeY } {}
        constexpr Rect(const T positionX, const T positionY, const vector2d<T> &size) noexcept : Rect{ positionX, positionY, size.x, size.y } {}

        constexpr Rect(const Rect&) noexcept = default;
        constexpr Rect &operator=(const Rect&) noexcept = default;
        constexpr Rect(Rect&&) noexcept = default;
        constexpr Rect &operator=(Rect&&) noexcept = default;

        template <typename U>
        constexpr Rect(const Rect<U>& rectangle) :
            left{ static_cast<T>(rectangle.left) }, top{ static_cast<T>(rectangle.top) },
            width{ static_cast<T>(rectangle.width) }, height{ static_cast<T>(rectangle.height) } {}

        constexpr const vector2d<T> center() const { return vector2d<T> {left + (width / static_cast<T>(2)),
            top + (height / static_cast<T>(2))}; }

        constexpr const bool operator==(const Rect &r) const
        {
            return (left == r.left && width == r.width && top == r.top && height == r.height);
        }

        constexpr const bool operator!=(const Rect &r) const
        {
            return !(operator==(r));
        }

        constexpr Rect& operator +=(const vector2d<T> &rhs)
        {
            left += rhs.x;
            top += rhs.y;
            return *this;
        }

        constexpr Rect& operator +=(const Rect &rhs)
        {
            left += rhs.left;
            top += rhs.top;
            return *this;
        }

        constexpr Rect& setLeftTop(const vector2d<T>&nleftTop) { left = nleftTop.x; top = nleftTop.y; return *this; }
        constexpr Rect& move(const vector2d<T>&relativePosition)  { left += relativePosition.x; top += relativePosition.y; return *this; }
        constexpr Rect& setSize(const vector2d<T>&nsize) { width = nsize.x; height = nsize.y; return *this;	}
        constexpr Rect& setRadiusFromCenter(const vector2d<T> &radius) {
            const auto c(center());
            left = static_cast<T>(c.x - radius.x);
            top = static_cast<T>(c.y - radius.y);
            width = static_cast<T>(radius.x * static_cast<T>(2));
            height = static_cast<T>(radius.y * static_cast<T>(2));
            return *this;
        }

        constexpr vector2d<T> radius() const noexcept {
            return { width / static_cast<T>(2) , height / static_cast<T>(2) };
        }

        constexpr const vector2d<T> leftTop() const noexcept { return vector2d<T>{left, top}; }
        constexpr const vector2d<T> size() const noexcept { return vector2d<T>{width, height}; }
        constexpr const T right() const noexcept { return left + width; }
        constexpr void setRight(const T& r) noexcept { width = r - left; }
        constexpr const T bottom() const  noexcept { return top + height; }
        constexpr void setBottom(const T& b) noexcept { height = b - top; }
        constexpr const vector2d<T> rightBottom() const noexcept { return vector2d<T>{right(), bottom()}; }
        constexpr const vector2d<T> rightTop() const  noexcept { return vector2d<T>{right(), top}; }
        constexpr const vector2d<T> leftBottom() const  noexcept { return vector2d<T>{left, bottom()}; }

        constexpr void move(const vector2d<T> &offset) const noexcept { ( *this ) += offset; };
        constexpr Rect moved(const vector2d<T> &offset) const noexcept { return (Rect(*this) += offset); };
        constexpr Rect resize(const vector2d<T> &sSize) const noexcept { return Rect{ left, top, width + sSize.x, height + sSize.y }; };
        constexpr Rect setRadiusFromCenter(const vector2d<T> &radius) const noexcept { Rect temp{ *this }; temp.setRadiusFromCenter(radius); return temp; }
        constexpr Rect moveResize(const vector2d<T> &offset, const vector2d<T> &sSize) const noexcept { return moved(offset).resize(sSize); };

        constexpr bool insideX(const vector2d<T>& v) const noexcept
        {
            return (v.x >= left && v.x < right());
        }

        constexpr bool insideY(const vector2d<T>& v) const noexcept
        {
            return (v.y >= top && v.y < bottom());
        }

        constexpr bool inside(const vector2d<T>& v) const noexcept
        {
            return insideX(v) && insideY(v);
        }
    };

    template <typename T>
    constexpr Rect<T> rectFromSize(const T sizeX, const T sizeY) noexcept { return { {},{}, vector2d<T>{sizeX,sizeY} }; }

    template <typename T>
    constexpr Rect<T> rectFromSize(const vector2d<T> &size) noexcept { return { {},{}, size }; }

    template <typename T>
    constexpr Rect<T> rectFromCenterAndRadius(const vector2d<T> &center, const vector2d<T> &radius) noexcept { return { center.x - radius.x,center.y - radius.y, center.x + radius.x, center.y + radius.y }; }

    template <typename T>
    constexpr Rect<T> rectFromCenterAndSize(const vector2d<T> &center, const vector2d<T> &size) noexcept { return rectFromCenterAndRadius<T>(center, size / static_cast<T>(2)); }

    template <typename T>
    constexpr Rect<T> operator +(const Rect<T> &lhs, const vector2d<T> &rhs) noexcept
    {
        return { lhs.left + rhs.x,lhs.top + rhs.y,lhs.width,lhs.height };
    }

    // Serialization operators
    template <typename T>
    constexpr write_stream& operator<<(write_stream & os, const Rect<T> &rect)
    {
        os << "{ {" << rect.left << "," << rect.top << "}, {" << rect.width << "," << rect.height << "} }";
        return os;
    }

    using Rectu8 = Rect<u8>;
    using Rects8 = Rect<s8>;
    using Rectu16 = Rect<u16>;
    using Rects16 = Rect<s16>;
    using Rects32 = Rect<s32>;
    using Rectu32 = Rect<u32>;
    using Rectf32 = Rect<f32>;
    using Rectf64 = Rect<f64>;
    using Rectst = Rect<size_type>;
}

#endif
