HTPS_PRAGMA_ONCE
#ifndef MTPS_VECTOR2D_INCLUDE_HPP
#define MTPS_VECTOR2D_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include <type_traits>

namespace htps
{
template <typename T>
class vector2d
{
public:
    constexpr vector2d& operator-() noexcept
    {
        x = -x;
        y = -y;
        return *this;
    }

    constexpr T dotProduct(vector2d const& p2) const noexcept
    {
        auto r(*this * p2);
        return r.x + r.y;
    }

    // Conversion operator
    template <typename Y>
    constexpr explicit operator vector2d<Y>() const noexcept
    {
        return vector2d<Y>{static_cast<Y>(x), static_cast<Y>(y)};
    }

    T x;
    T y;
};

template <typename T, typename Y>
constexpr vector2d<T> operator+(vector2d<T> const& lhs,
                                vector2d<Y> const& rhs) noexcept
{
    return {lhs.x + static_cast<T>(rhs.x), lhs.y + static_cast<T>(rhs.y)};
}

template <typename T, typename Y>
constexpr vector2d<T>& operator+=(vector2d<T>& lhs,
                                  vector2d<Y> const& rhs) noexcept
{
    lhs.x += static_cast<T>(rhs.x);
    lhs.y += static_cast<T>(rhs.y);
    return lhs;
}

template <typename T, typename Y>
constexpr vector2d<T>& operator-=(vector2d<T>& lhs,
                                  vector2d<Y> const& rhs) noexcept
{
    lhs.x -= static_cast<T>(rhs.x);
    lhs.y -= static_cast<T>(rhs.y);
    return lhs;
}

template <typename T, typename Y>
constexpr vector2d<T> operator-(vector2d<T> const& lhs,
                                vector2d<Y> const& rhs) noexcept
{
    return {lhs.x - static_cast<T>(rhs.x), lhs.y - static_cast<T>(rhs.y)};
}

template <typename T, typename Y>
constexpr vector2d<T>& operator*=(vector2d<T>& lhs,
                                  vector2d<Y> const& rhs) noexcept
{
    lhs.x *= static_cast<T>(rhs.x);
    lhs.y *= static_cast<T>(rhs.y);
    return lhs;
}

template <typename T, typename Y>
constexpr vector2d<T> operator*(vector2d<T> const& lhs,
                                vector2d<Y> const& rhs) noexcept
{
    return {lhs.x * static_cast<T>(rhs.x), lhs.y * static_cast<T>(rhs.y)};
}

template <typename T, typename Y>
constexpr vector2d<T>& operator*=(vector2d<T>& lhs, T const& scalar) noexcept
{
    lhs.x *= static_cast<T>(scalar);
    lhs.y *= static_cast<T>(scalar);
    return lhs;
}

template <typename T, typename Y>
constexpr vector2d<T> operator*(vector2d<T> const& lhs,
                                Y const& scalar) noexcept
{
    return {lhs.x * static_cast<T>(scalar), lhs.y * static_cast<T>(scalar)};
}

template <typename T, typename Y>
constexpr vector2d<T> operator*(Y const& scalar,
                                vector2d<T> const& rhs) noexcept
{
    return {static_cast<T>(scalar) * rhs.x, static_cast<T>(scalar) * rhs.y};
}

template <typename T, typename Y>
constexpr vector2d<T>& operator/=(vector2d<T>& lhs,
                                  vector2d<Y> const& rhs) noexcept
{
    lhs.x /= static_cast<T>(rhs.x);
    lhs.y /= static_cast<T>(rhs.y);
    return lhs;
}

template <typename T, typename Y>
constexpr vector2d<T> operator/(vector2d<T> const& lhs,
                                vector2d<Y> const& rhs) noexcept
{
    return {lhs.x / static_cast<T>(rhs.x), lhs.y / static_cast<T>(rhs.y)};
}

template <typename T, typename Y>
constexpr vector2d<T>& operator/=(vector2d<T>& lhs, T const& scalar) noexcept
{
    lhs.x /= static_cast<T>(scalar);
    lhs.y /= static_cast<T>(scalar);
    return lhs;
}

template <typename T, typename Y>
constexpr vector2d<T> operator/(vector2d<T> const& lhs,
                                Y const& scalar) noexcept
{
    return {lhs.x / static_cast<T>(scalar), lhs.y / static_cast<T>(scalar)};
}

template <typename T, typename Y>
constexpr vector2d<T> operator/(Y const& scalar,
                                vector2d<T> const& rhs) noexcept
{
    return {static_cast<T>(scalar) / rhs.x, static_cast<T>(scalar) / rhs.y};
}

template <typename T>
constexpr vector2d<T> operator-(vector2d<T> const& v2d) noexcept
{
    return vector2d<T>{-v2d.x, -v2d.y};
}

template <typename T, typename Y>
constexpr bool operator==(vector2d<T> const& lhs,
                          vector2d<Y> const& rhs) noexcept

{
    return (lhs.x == static_cast<T>(rhs.x) && lhs.y == static_cast<T>(rhs.y));
}

template <typename T, typename Y>
constexpr bool operator!=(vector2d<T> const& lhs,
                          vector2d<Y> const& rhs) noexcept
{
    return !(lhs == rhs);
}

// Serialization operators
template <typename T>
constexpr str& operator<<(str& os, vector2d<T> const& v2d)
{
    os << "{" << v2d.x << "," << v2d.y << "}";
    return os;
}

template <typename T>
constexpr str& operator>>(str& is, vector2d<T> const& v2d)
{
    return is;
}

static_assert(std::is_standard_layout_v<vector2d<u8>>,
              "vector2du8 has not standard layout");
static_assert(std::is_standard_layout_v<vector2d<f64>>,
              "vector2df64 has not standard layout");

using vector2du8  = vector2d<u8>;
using vector2ds8  = vector2d<s8>;
using vector2du16 = vector2d<u16>;
using vector2ds16 = vector2d<s16>;
using vector2du32 = vector2d<u32>;
using vector2ds32 = vector2d<s32>;
using vector2df   = vector2d<f32>;
using vector2dd   = vector2d<f64>;
using vector2dst  = vector2d<size_type>;
}  // namespace htps

#endif
