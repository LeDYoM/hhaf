#pragma once

#ifndef HAF_TIME_TIME_POINT_INCLUDE_HPP
#define HAF_TIME_TIME_POINT_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace haf::time
{
class TimePoint
{
public:
    using Rep = mtps::u64;

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
    mtps::u64 nanoseconds_;
};

constexpr TimePoint TimePoint_as_microseconds(const mtps::u64 micros) noexcept
{
    return TimePoint{micros * 1000U};
}

constexpr TimePoint TimePoint_as_miliseconds(const mtps::u64 millis) noexcept
{
    return TimePoint_as_microseconds(millis * 1000U);
}

constexpr TimePoint TimePoint_as_seconds(const mtps::u32 secs) noexcept
{
    return TimePoint_as_miliseconds(secs * 1000U);
}

constexpr TimePoint TimePoint_as_seconds(const mtps::f32 secs) noexcept
{
    return TimePoint_as_miliseconds(static_cast<mtps::u32>(secs * 1000U));
}

constexpr TimePoint operator+(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() + rhs.nanoseconds()};
}

constexpr TimePoint operator-(const TimePoint &lhs, const TimePoint &rhs) noexcept
{
    return {lhs.nanoseconds() - rhs.nanoseconds()};
}

constexpr TimePoint operator*(const TimePoint &lhs, const mtps::u64 scalar) noexcept
{
    return {lhs.nanoseconds() * scalar};
}

constexpr TimePoint operator*(const TimePoint &lhs, const mtps::f32 scalar) noexcept
{
    return {static_cast<mtps::u64>(static_cast<mtps::f32>(lhs.nanoseconds()) * scalar)};
}

constexpr TimePoint operator/(const TimePoint &lhs, const mtps::u64 scalar) noexcept
{
    return {static_cast<mtps::u64>(lhs.nanoseconds() / scalar)};
}

constexpr TimePoint operator/(const TimePoint &lhs, const mtps::f32 scalar) noexcept
{
    return {static_cast<mtps::u64>(static_cast<mtps::f32>(lhs.nanoseconds()) / scalar)};
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

constexpr mtps::str&operator<<(mtps::str &os, const TimePoint &tp) noexcept
{
    os << tp.nanoseconds();
    return os;
}
} // namespace haf

#endif
