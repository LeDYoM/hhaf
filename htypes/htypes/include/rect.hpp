#ifndef MTPS_HTYPES_RECT_INCLUDE_HPP
#define MTPS_HTYPES_RECT_INCLUDE_HPP

#include "types.hpp"
#include "vector2d.hpp"

namespace htps
{
template <typename T>
struct Rect
{
    T left{}, top{}, width{}, height{};

    constexpr Rect() noexcept = default;
    constexpr Rect(T const rectLeft,
                   T const rectTop,
                   T const rectWidth,
                   T const rectHeight) noexcept :
        left{std::move(rectLeft)},
        top{std::move(rectTop)},
        width{std::move(rectWidth)},
        height{std::move(rectHeight)}
    {}

    constexpr Rect(vector2d<T> const& position,
                   vector2d<T> const& size) noexcept :
        Rect{position.x, position.y, size.x, size.y}
    {}

    constexpr Rect(vector2d<T> const& position,
                   T const sizeX,
                   T const sizeY) noexcept :
        Rect{position.x, position.y, std::move(sizeX), std::move(sizeY)}
    {}

    constexpr Rect(T const positionX,
                   T const positionY,
                   vector2d<T> const& size) noexcept :
        Rect{std::move(positionX), std::move(positionY), size.x, size.y}
    {}

    constexpr Rect(Rect const&) noexcept = default;
    constexpr Rect& operator=(Rect const&) noexcept = default;
    constexpr Rect(Rect&&) noexcept                 = default;
    constexpr Rect& operator=(Rect&&) noexcept = default;

    template <typename U>
    constexpr Rect(Rect<U> const& rectangle) :
        left{static_cast<T>(rectangle.left)},
        top{static_cast<T>(rectangle.top)},
        width{static_cast<T>(rectangle.width)},
        height{static_cast<T>(rectangle.height)}
    {}

    [[nodiscard]] constexpr vector2d<T> center() const noexcept
    {
        return vector2d<T>{left + (width / static_cast<T>(2)),
                           top + (height / static_cast<T>(2))};
    }

    [[nodiscard]] constexpr bool operator==(Rect const& r) const
    {
        return (left == r.left && width == r.width && top == r.top &&
                height == r.height);
    }

    [[nodiscard]] constexpr bool operator!=(Rect const& r) const
    {
        return !(*this == r);
    }

    constexpr Rect& operator+=(vector2d<T> const& rhs)
    {
        left += rhs.x;
        top += rhs.y;
        return *this;
    }

    constexpr Rect& operator+=(Rect const& rhs) noexcept
    {
        left += rhs.left;
        top += rhs.top;
        return *this;
    }

    constexpr Rect& setLeftTop(vector2d<T> const& nleftTop) noexcept
    {
        left = nleftTop.x;
        top  = nleftTop.y;
        return *this;
    }

    constexpr Rect& move(vector2d<T> const& relativePosition) noexcept
    {
        left += relativePosition.x;
        top += relativePosition.y;
        return *this;
    }

    constexpr Rect& setSize(vector2d<T> const& nsize) noexcept
    {
        width  = nsize.x;
        height = nsize.y;
        return *this;
    }

    constexpr Rect& setRadiusFromCenter(vector2d<T> const& radius) noexcept
    {
        const auto c{center()};
        left   = static_cast<T>(c.x - radius.x);
        top    = static_cast<T>(c.y - radius.y);
        width  = static_cast<T>(radius.x * static_cast<T>(2));
        height = static_cast<T>(radius.y * static_cast<T>(2));
        return *this;
    }

    [[nodiscard]] constexpr vector2d<T> radius() const noexcept
    {
        return {width / static_cast<T>(2), height / static_cast<T>(2)};
    }

    [[nodiscard]] constexpr vector2d<T> leftTop() const noexcept
    {
        return vector2d<T>{left, top};
    }

    [[nodiscard]] constexpr vector2d<T> size() const noexcept
    {
        return vector2d<T>{width, height};
    }

    [[nodiscard]] constexpr T right() const noexcept { return left + width; }
    constexpr void setRight(T const& r) noexcept { width = r - left; }
    [[nodiscard]] constexpr T bottom() const noexcept { return top + height; }
    constexpr void setBottom(T const& b) noexcept { height = b - top; }
    [[nodiscard]] constexpr vector2d<T> rightBottom() const noexcept
    {
        return vector2d<T>{right(), bottom()};
    }

    [[nodiscard]] constexpr vector2d<T> rightTop() const noexcept
    {
        return vector2d<T>{right(), top};
    }

    [[nodiscard]] constexpr vector2d<T> leftBottom() const noexcept
    {
        return vector2d<T>{left, bottom()};
    }

    [[nodiscard]] constexpr Rect moved(vector2d<T> const& offset) const noexcept
    {
        return (Rect{*this} += offset);
    }

    [[nodiscard]] constexpr Rect resize(const vector2d<T>& sSize) const noexcept
    {
        return Rect{left, top, width + sSize.x, height + sSize.y};
    }

    [[nodiscard]] constexpr Rect setRadiusFromCenter(const vector2d<T>& radius) const noexcept
    {
        Rect temp{*this};
        temp.setRadiusFromCenter(radius);
        return temp;
    }

    [[nodiscard]] constexpr Rect moveResize(
        const vector2d<T>& offset,
        const vector2d<T>& sSize) const noexcept
    {
        return moved(offset).resize(sSize);
    };

    [[nodiscard]] constexpr bool insideX(vector2d<T> const& v) const noexcept
    {
        return (v.x >= left && v.x < right());
    }

    [[nodiscard]] constexpr bool insideY(vector2d<T> const& v) const noexcept
    {
        return (v.y >= top && v.y < bottom());
    }

    [[nodiscard]] constexpr bool inside(vector2d<T> const& v) const noexcept
    {
        return insideX(v) && insideY(v);
    }

    template <typename U>
    constexpr void scaleInverseX(U const& scalar)
    {
        left /= static_cast<T>(scalar);
        width /= static_cast<T>(scalar);
    }

    template <typename U>
    constexpr void scaleInverseY(U const& scalar)
    {
        top /= static_cast<T>(scalar);
        height /= static_cast<T>(scalar);
    }

    template <typename U>
    constexpr void scaleInverse(vector2d<U> const& scalar)
    {
        scaleInverseX(scalar.x);
        scaleInverseY(scalar.y);
    }

    template <typename U>
    constexpr void scaleInverse(U const& scalar)
    {
        scaleInverseX(scalar);
        scaleInverseY(scalar);
    }

    template <typename U>
    constexpr void scaleX(U const& scalar)
    {
        left *= static_cast<T>(scalar);
        width *= static_cast<T>(scalar);
    }

    template <typename U>
    constexpr void scaleY(U const& scalar)
    {
        top *= static_cast<T>(scalar);
        height *= static_cast<T>(scalar);
    }

    template <typename U>
    constexpr void scale(U const& scalar)
    {
        scaleX(scalar);
        scaleY(scalar);
    }

    template <typename U>
    constexpr void scale(vector2d<U> const& scalar)
    {
        scaleX(scalar.x);
        scaleY(scalar.y);
    }
};

template <typename T>
[[nodiscard]] constexpr Rect<T> rectFromSize(T const sizeX,
                                             T const sizeY) noexcept
{
    return {{}, {}, vector2d<T>{sizeX, sizeY}};
}

template <typename T>
[[nodiscard]] constexpr Rect<T> rectFromSize(vector2d<T> const& size) noexcept
{
    return {{}, {}, size};
}

template <typename T>
[[nodiscard]] constexpr Rect<T> rectFromCenterAndRadius(
    vector2d<T> const& center,
    vector2d<T> const& radius) noexcept
{
    return {center.x - radius.x, center.y - radius.y,
            radius.x * static_cast<T>(2), radius.y * static_cast<T>(2)};
}

template <typename T>
[[nodiscard]] constexpr Rect<T> rectFromCenterAndSize(
    vector2d<T> const& center,
    vector2d<T> const& size) noexcept
{
    return rectFromCenterAndRadius<T>(center, size / static_cast<T>(2));
}

template <typename T>
constexpr Rect<T> operator+(Rect<T> const& lhs, vector2d<T> const& rhs) noexcept
{
    return {lhs.left + rhs.x, lhs.top + rhs.y, lhs.width, lhs.height};
}

// Serialization operators
template <typename T>
constexpr str& operator<<(str& os, Rect<T> const& rect)
{
    os << "{ {" << rect.left << "," << rect.top << "}, {" << rect.width << ","
       << rect.height << "} }";
    return os;
}

using Rectu8  = Rect<u8>;
using Rects8  = Rect<s8>;
using Rectu16 = Rect<u16>;
using Rects16 = Rect<s16>;
using Rects32 = Rect<s32>;
using Rectu32 = Rect<u32>;
using Rectf32 = Rect<f32>;
using Rectf64 = Rect<f64>;
using Rectst  = Rect<size_type>;
}  // namespace htps

#endif
