FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VECTOR3D_INCLUDE_HPP
#define FACIL_MATH_VECTOR3D_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>
#include <htypes/include/str.hpp>

#include <type_traits>

namespace fmath
{
namespace tps = htps;

template <typename T>
class vector3d
{
public:
    static constexpr tps::u16 kNumElements{3U};
    using value_type = T;

    constexpr vector3d() noexcept = default;

    explicit constexpr vector3d(vector2d<T> const& v) noexcept :
        x{v.x}, y{v.y}, z{static_cast<T>(0)}
    {}

    constexpr vector3d(T const _x, T const _y, T const _z) noexcept :
        x{_x}, y{_y}, z{_z}
    {}

    constexpr vector3d(T const _x, T const _y) noexcept : x{_x}, y{_y}, z{} {}

    // Conversion operator
    template <typename Y>
    constexpr explicit operator vector3d<Y>() const noexcept
    {
        return vector3d<Y>{static_cast<Y>(x), static_cast<Y>(y),
                           static_cast<Y>(z)};
    }

    template <typename Y>
    constexpr vector3d& operator+=(vector3d<Y> const& rhs) noexcept
    {
        x += static_cast<T>(rhs.x);
        y += static_cast<T>(rhs.y);
        z += static_cast<T>(rhs.z);
        return *this;
    }

    template <typename Y>
    constexpr vector3d& operator-=(vector3d<Y> const& rhs) noexcept
    {
        x -= static_cast<T>(rhs.x);
        y -= static_cast<T>(rhs.y);
        z -= static_cast<T>(rhs.z);
        return *this;
    }

    template <typename Y>
    constexpr vector3d& move(vector3d<Y> const& rhs) noexcept
    {
        *this += rhs;
        return *this;
    }

    template <typename Y>
    constexpr vector3d& moveX(Y const x_) noexcept
    {
        return this->move(vector3d<Y>{x_, Y{}, Y{}});
    }

    template <typename Y>
    constexpr vector3d& moveY(Y const y_) noexcept
    {
        return this->move(vector3d<Y>{Y{}, y_, Y{}});
    }

    template <typename Y>
    constexpr vector3d& moveZ(Y const z_) noexcept
    {
        return this->move(vector3d<Y>{Y{}, Y{}, z_});
    }

    template <typename Y>
    constexpr vector3d& operator*=(vector3d<Y> const& rhs) noexcept
    {
        x *= static_cast<T>(rhs.x);
        y *= static_cast<T>(rhs.y);
        z *= static_cast<T>(rhs.z);
        return *this;
    }

    template <typename Y>
    constexpr vector3d& operator*=(Y const& scalar) noexcept
    {
        x *= static_cast<T>(scalar);
        y *= static_cast<T>(scalar);
        z *= static_cast<T>(scalar);
        return *this;
    }

    template <typename Y>
    constexpr vector3d& operator/=(vector3d<Y> const& rhs) noexcept
    {
        x /= static_cast<T>(rhs.x);
        y /= static_cast<T>(rhs.y);
        z /= static_cast<T>(rhs.z);
        return *this;
    }

    template <typename Y>
    constexpr vector3d operator/=(Y const& scalar) noexcept
    {
        x /= static_cast<T>(scalar);
        y /= static_cast<T>(scalar);
        z /= static_cast<T>(scalar);
        return *this;
    }

    T x;
    T y;
    T z;
};

template <typename T, typename Y>
constexpr vector3d<T> operator+(vector3d<T> const& lhs,
                                vector3d<Y> const& rhs) noexcept
{
    return vector3d<T>{lhs} += rhs;
}

template <typename T, typename Y>
constexpr vector3d<T> operator-(vector3d<T> const& lhs,
                                vector3d<Y> const& rhs) noexcept
{
    return vector3d<T>{lhs} -= rhs;
}

template <typename T, typename Y>
constexpr vector3d<T> operator*(Y const& scalar,
                                vector3d<T> const& rhs) noexcept
{
    return vector3d<T>{rhs} *= scalar;
}

template <typename T, typename Y>
constexpr vector3d<T> operator*(vector3d<T> const& lhs,
                                Y const& scalar) noexcept
{
    return scalar * lhs;
}

template <typename T, typename Y>
constexpr vector3d<T> operator*(vector3d<T> const& lhs,
                                vector3d<Y> const& rhs) noexcept
{
    return vector3d<T>{lhs} *= rhs;
}

template <typename T, typename Y>
constexpr vector3d<Y> operator/(Y const& scalar,
                                vector3d<T> const& rhs) noexcept
{
    return vector3d<Y>{scalar / static_cast<Y>(rhs.x),
                       scalar / static_cast<Y>(rhs.y),
                       scalar / static_cast<Y>(rhs.z)};
}

template <typename T, typename Y>
constexpr vector3d<T> operator/(vector3d<T> const& lhs,
                                Y const& scalar) noexcept
{
    return vector3d<T>{lhs} /= scalar;
}

template <typename T, typename Y>
constexpr vector3d<T> operator/(vector3d<T> const& lhs,
                                vector3d<Y> const& rhs) noexcept
{
    return vector3d<T>{lhs} /= rhs;
}

template <typename T>
constexpr vector3d<T> operator-(vector3d<T> const& v) noexcept
{
    return vector3d<T>{-v.x, -v.y, -v.z};
}

template <typename T, typename Y>
constexpr bool operator==(vector3d<T> const& lhs,
                          vector3d<Y> const& rhs) noexcept
{
    return (lhs.x == static_cast<T>(rhs.x) && lhs.y == static_cast<T>(rhs.y) &&
            lhs.z == static_cast<T>(rhs.z));
}

template <typename T, typename Y>
constexpr bool operator!=(vector3d<T> const& lhs,
                          vector3d<Y> const& rhs) noexcept
{
    return !(lhs == rhs);
}

// Serialization operators
template <typename T>
constexpr htps::str& operator<<(htps::str& os, vector3d<T> const& v3d)
{
    os << "{" << v3d.x << "," << v3d.y << "," << v3d.z << "}";
    return os;
}

template <typename T>
constexpr htps::str& operator>>(htps::str& is, vector3d<T> const& v3d)
{
    return is;
}

static_assert(std::is_standard_layout_v<vector3d<tps::u8>>,
              "vector3du8 has not standard layout");
static_assert(std::is_standard_layout_v<vector3d<tps::f64>>,
              "vector3df64 has not standard layout");

static_assert(std::is_trivial_v<vector3d<tps::f32>>, "vector3df32 is not trivial");

using vector3du8  = vector3d<tps::u8>;
using vector3ds8  = vector3d<tps::s8>;
using vector3du16 = vector3d<tps::u16>;
using vector3ds16 = vector3d<tps::s16>;
using vector3du32 = vector3d<tps::u32>;
using vector3ds32 = vector3d<tps::s32>;
using vector3df   = vector3d<tps::f32>;
using vector3dd   = vector3d<tps::f64>;
using vector3dst  = vector3d<tps::size_type>;
}  // namespace fmath

#endif
