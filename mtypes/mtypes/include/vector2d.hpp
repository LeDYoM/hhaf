#ifndef MTPS_VECTOR2D_INCLUDE_HPP
#define MTPS_VECTOR2D_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"

namespace mtps
{
template <typename T>
class vector2d
{
public:
    constexpr vector2d& operator+=(const vector2d& right) noexcept
    {
        x += right.x;
        y += right.y;
        return *this;
    }

    template <typename V>
    constexpr vector2d& operator+=(const vector2d& right) noexcept
    {
        x += static_cast<T>(right.x);
        y += static_cast<T>(right.y);
        return *this;
    }

    constexpr vector2d& operator-=(const vector2d& right) noexcept
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }

    constexpr vector2d& operator*=(const vector2d& right) noexcept
    {
        x *= right.x;
        y *= right.y;
        return *this;
    }

    constexpr vector2d& operator*=(const T& scalar) noexcept
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr vector2d& operator/=(const vector2d& right)
    {
        x /= right.x;
        y /= right.y;
        return *this;
    }

    constexpr vector2d& operator/=(const T& scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr vector2d& operator-() noexcept
    {
        x = -x;
        y = -y;
        return *this;
    }

    constexpr T dotProduct(const vector2d& p2) const noexcept
    {
        auto r(*this * p2);
        return r.x + r.y;
    }

    template <typename V>
    static constexpr bool IsNotInnerType =
        !std::is_same_v<std::decay_t<T>, std::decay_t<V>>;

    constexpr vector2d operator+(const vector2d& right) const noexcept
    {
        return (vector2d(*this) += right);
    }

    template <typename V, typename = std::enable_if_t<IsNotInnerType<V>>>
    constexpr vector2d operator+(const vector2d<V>& right) const noexcept
    {
        return (vector2d(*this) += right);
    }

    constexpr vector2d operator-(const vector2d& right) const noexcept
    {
        return (vector2d(*this) -= right);
    }

    constexpr vector2d operator*(const vector2d& right) const noexcept
    {
        return (vector2d(*this) *= right);
    }
    constexpr vector2d operator*(const T& right) const noexcept
    {
        return (vector2d(*this) *= right);
    }
    template <typename V,
              typename = std::enable_if_t<
                  !std::is_same_v<std::decay_t<T>, std::decay_t<V>>>>
    constexpr vector2d operator*(const vector2d<V>& right) const noexcept
    {
        return (vector2d(*this) *= static_cast<vector2d>(right));
    }

    constexpr vector2d operator/(const vector2d& right) const noexcept
    {
        return (vector2d(*this) /= right);
    }
    constexpr vector2d operator/(const T& right) const noexcept
    {
        return (vector2d(*this) /= right);
    }
    template <typename V,
              typename = std::enable_if_t<
                  !std::is_same_v<std::decay_t<T>, std::decay_t<V>>>>
    constexpr vector2d operator/(const vector2d<V>& right) const noexcept
    {
        return (vector2d(*this) /= static_cast<vector2d>(right));
    }

    constexpr bool operator==(const vector2d& right) const noexcept
    {
        return (x == right.x && y == right.y);
    }
    constexpr bool operator!=(const vector2d& right) const noexcept
    {
        return !(*operator==(right));
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

template <typename T>
constexpr vector2d<T> operator/(const vector2d<T>& lhs,
                                const vector2d<T>& rhs) noexcept
{
    return lhs / rhs;
}

template <typename T>
constexpr vector2d<T> operator-(const vector2d<T>& v2d) noexcept
{
    return vector2d<T>{-v2d.x, -v2d.y};
}

// Serialization operators
template <typename T>
constexpr str& operator<<(str& os, const vector2d<T>& v2d)
{
    os << "{" << v2d.x << "," << v2d.y << "}";
    return os;
}

template <typename T>
constexpr str& operator>>(str& is, const vector2d<T>& v2d)
{
    return is;
}

static_assert(std::is_pod_v<vector2d<u8>>, "vector2du8 is not a pod");
static_assert(std::is_pod_v<vector2d<f64>>, "vector2df64 is not a pod");

using vector2du8  = vector2d<u8>;
using vector2ds8  = vector2d<s8>;
using vector2du16 = vector2d<u16>;
using vector2ds16 = vector2d<s16>;
using vector2du32 = vector2d<u32>;
using vector2ds32 = vector2d<s32>;
using vector2df   = vector2d<f32>;
using vector2dd   = vector2d<f64>;
using vector2dst  = vector2d<size_type>;
}  // namespace mtps

#endif
