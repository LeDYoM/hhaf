#pragma once

#ifndef LIB_TIME_TIME_POINT_INCLUDE_HPP
#define LIB_TIME_TIME_POINT_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace lib::time
{
class TimePoint
{
public:
    using Rep = u64;

    constexpr TimePoint(const Rep nanoseconds = Rep{0U}) noexcept
        : nanoseconds_{nanoseconds} {}

    constexpr Rep nanoseconds() const noexcept { return nanoseconds_; }
    constexpr Rep microseconds() const noexcept { return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000U)); }
    constexpr Rep milliseconds() const noexcept { return static_cast<Rep>(microseconds() / static_cast<Rep>(1000U)); }
    constexpr Rep seconds() const noexcept { return static_cast<Rep>(milliseconds() / static_cast<Rep>(1000U)); }

    constexpr TimePoint &operator+=(const TimePoint &other) noexcept
    {
        this->nanoseconds_ += other.nanoseconds();
        return *this;
    }

    constexpr TimePoint &operator-=(const TimePoint &other) noexcept
    {
        this->nanoseconds_ -= other.nanoseconds();
        return *this;
    }

private:
    u64 nanoseconds_;
};

constexpr TimePoint TimePoint_as_microseconds(const u64 micros) noexcept
{
    return TimePoint{micros * 1000U};
}

constexpr TimePoint TimePoint_as_miliseconds(const u64 millis) noexcept
{
    return TimePoint_as_microseconds(millis * 1000U);
}

constexpr TimePoint TimePoint_as_seconds(const u32 secs) noexcept
{
    return TimePoint_as_miliseconds(secs * 1000U);
}

constexpr TimePoint TimePoint_as_seconds(const f32 secs) noexcept
{
    return TimePoint_as_miliseconds(static_cast<u32>(secs * 1000U));
}

constexpr TimePoint operator+(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() + rhs.nanoseconds()};
}

constexpr TimePoint operator-(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() - rhs.nanoseconds()};
}

constexpr TimePoint operator*(const TimePoint &lhs, const u64 scalar) noexcept
{
    return {lhs.nanoseconds() * scalar};
}

constexpr TimePoint operator*(const TimePoint &lhs, const f32 scalar) noexcept
{
    return {static_cast<u64>(static_cast<f32>(lhs.nanoseconds()) * scalar)};
}

constexpr TimePoint operator/(const TimePoint &lhs, const u64 scalar) noexcept
{
    return {static_cast<u64>(lhs.nanoseconds() / scalar)};
}

constexpr TimePoint operator/(const TimePoint &lhs, const f32 scalar) noexcept
{
    return {static_cast<u64>(static_cast<f32>(lhs.nanoseconds()) / scalar)};
}

constexpr bool operator<(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() < rhs.nanoseconds()};
}

constexpr bool operator>(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() > rhs.nanoseconds()};
}

constexpr bool operator<=(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() <= rhs.nanoseconds()};
}

constexpr bool operator>=(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() >= rhs.nanoseconds()};
}

constexpr bool operator==(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() == rhs.nanoseconds()};
}

constexpr bool operator!=(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() != rhs.nanoseconds()};
}

constexpr str &operator<<(str &os, const TimePoint &tp) noexcept
{
    os << tp.nanoseconds();
    return os;
}
} // namespace lib

#endif
