FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VECTOR2D_INCLUDE_HPP
#define FACIL_MATH_VECTOR2D_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <type_traits>

namespace fmath
{
namespace tps = htps;

template <typename T>
class vector2d
{
public:
    static constexpr htps::u16 kNumElements{2U};
    using value_type = T;

    constexpr vector2d() noexcept {}

    constexpr vector2d(T const _x, T const _y) noexcept : x{_x}, y{_y} {}

    // Conversion operator
    template <typename Y>
    constexpr explicit operator vector2d<Y>() const noexcept
    {
        return vector2d<Y>{static_cast<Y>(x), static_cast<Y>(y)};
    }

    template <typename Y>
    constexpr vector2d& operator+=(vector2d<Y> const& rhs) noexcept
    {
        x += static_cast<T>(rhs.x);
        y += static_cast<T>(rhs.y);
        return *this;
    }

    template <typename Y>
    constexpr vector2d& operator-=(vector2d<Y> const& rhs) noexcept
    {
        x -= static_cast<T>(rhs.x);
        y -= static_cast<T>(rhs.y);
        return *this;
    }

    template <typename Y>
    constexpr vector2d& operator*=(vector2d<Y> const& rhs) noexcept
    {
        x *= static_cast<T>(rhs.x);
        y *= static_cast<T>(rhs.y);
        return *this;
    }

    template <typename Y>
    constexpr vector2d& operator*=(Y const& scalar) noexcept
    {
        x *= static_cast<T>(scalar);
        y *= static_cast<T>(scalar);
        return *this;
    }

    template <typename Y>
    constexpr vector2d& operator/=(vector2d<Y> const& rhs) noexcept
    {
        x /= static_cast<T>(rhs.x);
        y /= static_cast<T>(rhs.y);
        return *this;
    }

    template <typename Y>
    constexpr vector2d operator/=(Y const& scalar) noexcept
    {
        x /= static_cast<T>(scalar);
        y /= static_cast<T>(scalar);
        return *this;
    }

    T x;
    T y;
};

template <typename T, typename Y>
constexpr vector2d<T> operator+(vector2d<T> const& lhs,
                                vector2d<Y> const& rhs) noexcept
{
    return vector2d<T>{lhs} += rhs;
}

template <typename T, typename Y>
constexpr vector2d<T> operator-(vector2d<T> const& lhs,
                                vector2d<Y> const& rhs) noexcept
{
    return vector2d<T>{lhs} -= rhs;
}

template <typename T, typename Y>
constexpr vector2d<T> operator*(Y const& scalar,
                                vector2d<T> const& rhs) noexcept
{
    return vector2d<T>{rhs} *= scalar;
}

template <typename T, typename Y>
constexpr vector2d<T> operator*(vector2d<T> const& lhs,
                                Y const& scalar) noexcept
{
    return scalar * lhs;
}

template <typename T, typename Y>
constexpr vector2d<T> operator*(vector2d<T> const& lhs,
                                vector2d<Y> const& rhs) noexcept
{
    return vector2d<T>{lhs} *= rhs;
}

template <typename T, typename Y>
constexpr vector2d<Y> operator/(Y const& scalar,
                                vector2d<T> const& rhs) noexcept
{
    return vector2d<Y>{scalar / static_cast<Y>(rhs.x),
                       scalar / static_cast<Y>(rhs.y)};
}

template <typename T, typename Y>
constexpr vector2d<T> operator/(vector2d<T> const& lhs,
                                Y const& scalar) noexcept
{
    return vector2d<T>{lhs} /= scalar;
}

template <typename T, typename Y>
constexpr vector2d<T> operator/(vector2d<T> const& lhs,
                                vector2d<Y> const& rhs) noexcept
{
    return vector2d<T>{lhs} /= rhs;
}

template <typename T>
constexpr vector2d<T> operator-(vector2d<T> const& v) noexcept
{
    return vector2d<T>{-v.x, -v.y};
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
constexpr htps::str& operator<<(htps::str& os, vector2d<T> const& v2d)
{
    os << "{" << v2d.x << "," << v2d.y << "}";
    return os;
}

template <typename T>
constexpr htps::str& operator>>(htps::str& is, vector2d<T> const& v2d)
{
    return is;
}

static_assert(std::is_standard_layout_v<vector2d<tps::u8>>,
              "vector2du8 has not standard layout");
static_assert(std::is_standard_layout_v<vector2d<tps::f64>>,
              "vector2df64 has not standard layout");

//static_assert(std::is_trivial_v<vector2d<tps::f32>>,
//              "vector2df32 is not trivial");

using vector2du8  = vector2d<tps::u8>;
using vector2ds8  = vector2d<tps::s8>;
using vector2du16 = vector2d<tps::u16>;
using vector2ds16 = vector2d<tps::s16>;
using vector2du32 = vector2d<tps::u32>;
using vector2ds32 = vector2d<tps::s32>;
using vector2df   = vector2d<tps::f32>;
using vector2dd   = vector2d<tps::f64>;
using vector2dst  = vector2d<tps::size_type>;
}  // namespace fmath

#endif
