FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VECTOR4D_INCLUDE_HPP
#define FACIL_MATH_VECTOR4D_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <facil_math/include/vector3d.hpp>
#include <htypes/include/str.hpp>

#include <type_traits>

namespace fmath
{
namespace tps = htps;

template <typename T>
class vector4d
{
public:
    static constexpr tps::u16 kNumElements{4U};
    using value_type = T;

    constexpr bool operator==(vector4d const& rhs) const noexcept = default;

    constexpr vector4d() noexcept = default;

    constexpr vector4d(vector3d<T> const& v, T _w) noexcept :
        x{v.x}, y{v.y}, z{v.z}, w{_w}
    {}

    constexpr explicit vector4d(vector3d<T> const& v) noexcept :
        x{v.x}, y{v.y}, z{v.z}, w{static_cast<T>(0)}
    {}

    constexpr explicit vector4d(vector2d<T> const& v) noexcept :
        x{v.x}, y{v.y}, z{static_cast<T>(0)}, w{static_cast<T>(0)}
    {}

    constexpr vector4d(T const _x, T const _y, T const _z, T const _w) noexcept
        :
        x{_x}, y{_y}, z{_z}, w{_w}
    {}

    constexpr vector4d(T const _x, T const _y, T const _z) noexcept :
        x{_x}, y{_y}, z{_z}, w{}
    {}

    constexpr vector4d(T const _x, T const _y) noexcept : x{_x}, y{_y}, z{}, w{}
    {}

    // Conversion operator
    template <typename Y>
    constexpr explicit operator vector4d<Y>() const noexcept
    {
        return vector4d<Y>{static_cast<Y>(x), static_cast<Y>(y),
                           static_cast<Y>(z), static_cast<Y>(w)};
    }

    template <typename Y>
    constexpr vector4d& operator+=(vector4d<Y> const& rhs) noexcept
    {
        x += static_cast<T>(rhs.x);
        y += static_cast<T>(rhs.y);
        z += static_cast<T>(rhs.z);
        w += static_cast<T>(rhs.w);
        return *this;
    }

    template <typename Y>
    constexpr vector4d& operator-=(vector4d<Y> const& rhs) noexcept
    {
        x -= static_cast<T>(rhs.x);
        y -= static_cast<T>(rhs.y);
        z -= static_cast<T>(rhs.z);
        w -= static_cast<T>(rhs.w);
        return *this;
    }

    template <typename Y>
    constexpr vector4d& operator*=(vector4d<Y> const& rhs) noexcept
    {
        x *= static_cast<T>(rhs.x);
        y *= static_cast<T>(rhs.y);
        z *= static_cast<T>(rhs.z);
        w *= static_cast<T>(rhs.w);
        return *this;
    }

    template <typename Y>
    constexpr vector4d& operator*=(Y const& scalar) noexcept
    {
        x *= static_cast<T>(scalar);
        y *= static_cast<T>(scalar);
        z *= static_cast<T>(scalar);
        w *= static_cast<T>(scalar);
        return *this;
    }

    template <typename Y>
    constexpr vector4d& operator/=(vector4d<Y> const& rhs) noexcept
    {
        x /= static_cast<T>(rhs.x);
        y /= static_cast<T>(rhs.y);
        z /= static_cast<T>(rhs.z);
        w /= static_cast<T>(rhs.w);
        return *this;
    }

    template <typename Y>
    constexpr vector4d operator/=(Y const& scalar) noexcept
    {
        x /= static_cast<T>(scalar);
        y /= static_cast<T>(scalar);
        z /= static_cast<T>(scalar);
        w /= static_cast<T>(scalar);
        return *this;
    }

    T x;
    T y;
    T z;
    T w;
};

template <typename T, typename Y>
constexpr vector4d<T> operator+(vector4d<T> const& lhs,
                                vector4d<Y> const& rhs) noexcept
{
    return vector4d<T>{lhs} += rhs;
}

template <typename T, typename Y>
constexpr vector4d<T> operator-(vector4d<T> const& lhs,
                                vector4d<Y> const& rhs) noexcept
{
    return vector4d<T>{lhs} -= rhs;
}

template <typename T, typename Y>
constexpr vector4d<T> operator*(Y const& scalar,
                                vector4d<T> const& rhs) noexcept
{
    return vector4d<T>{rhs} *= scalar;
}

template <typename T, typename Y>
constexpr vector4d<T> operator*(vector4d<T> const& lhs,
                                Y const& scalar) noexcept
{
    return scalar * lhs;
}

template <typename T, typename Y>
constexpr vector4d<T> operator*(vector4d<T> const& lhs,
                                vector4d<Y> const& rhs) noexcept
{
    return vector4d<T>{lhs} *= rhs;
}

template <typename T, typename Y>
constexpr vector4d<Y> operator/(Y const& scalar,
                                vector4d<T> const& rhs) noexcept
{
    return vector4d<Y>{
        scalar / static_cast<Y>(rhs.x), scalar / static_cast<Y>(rhs.y),
        scalar / static_cast<Y>(rhs.z), scalar / static_cast<Y>(rhs.w)};
}

template <typename T, typename Y>
constexpr vector4d<T> operator/(vector4d<T> const& lhs,
                                Y const& scalar) noexcept
{
    return vector4d<T>{lhs} /= scalar;
}

template <typename T, typename Y>
constexpr vector4d<T> operator/(vector4d<T> const& lhs,
                                vector4d<Y> const& rhs) noexcept
{
    return vector4d<T>{lhs} /= rhs;
}

template <typename T>
constexpr vector4d<T> operator-(vector4d<T> const& v) noexcept
{
    return vector4d<T>{-v.x, -v.y, -v.z, -v.w};
}

template <typename T, typename Y>
constexpr bool operator==(vector4d<T> const& lhs,
                          vector4d<Y> const& rhs) noexcept
{
    return (lhs.x == static_cast<T>(rhs.x) && lhs.y == static_cast<T>(rhs.y) &&
            lhs.z == static_cast<T>(rhs.z) && lhs.w == static_cast<T>(rhs.w));
}

template <typename T, typename Y>
constexpr bool operator!=(vector4d<T> const& lhs,
                          vector4d<Y> const& rhs) noexcept
{
    return !(lhs == rhs);
}

// Serialization operators
template <typename T>
constexpr htps::str& operator<<(htps::str& os, vector4d<T> const& v4d)
{
    os << "{" << v4d.x << "," << v4d.y << "," << v4d.z << "," << v4d.w << "}";
    return os;
}

template <typename T>
constexpr htps::str& operator>>(htps::str& is, vector4d<T> const& v4d)
{
    return is;
}

static_assert(std::is_standard_layout_v<vector4d<tps::u8>>,
              "vector4du8 has not standard layout");
static_assert(std::is_standard_layout_v<vector4d<tps::f64>>,
              "vector4df64 has not standard layout");

static_assert(std::is_trivial_v<vector4d<tps::f32>>,
              "vector4df32 is not trivial");

using vector4du8  = vector4d<tps::u8>;
using vector4ds8  = vector4d<tps::s8>;
using vector4du16 = vector4d<tps::u16>;
using vector4ds16 = vector4d<tps::s16>;
using vector4du32 = vector4d<tps::u32>;
using vector4ds32 = vector4d<tps::s32>;
using vector4df   = vector4d<tps::f32>;
using vector4dd   = vector4d<tps::f64>;
using vector4dst  = vector4d<tps::size_type>;
}  // namespace fmath

#endif
