#pragma once

#ifndef HAF_TIME_TIME_POINT_INCLUDE_HPP
#define HAF_TIME_TIME_POINT_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace haf::time
{
/**
 * @brief Type representing a point in time.
 * It includes functions to convert and set different points in time.
 */
class TimePoint
{
public:
    using Rep = mtps::u64;  //<! Type to internally represent the data.

    constexpr TimePoint() noexcept : nanoseconds_{Rep{0U}} {}

    /**
     * @brief Constructor taking one parameter
     * @param nanoseconds Data to initialize the time point
     */
    constexpr TimePoint(Rep nanoseconds) noexcept :
        nanoseconds_{std::move(nanoseconds)}
    {}

    /**
     * @brief Return the time point as nanoseconds
     * @return constexpr Rep The value
     */
    constexpr Rep nanoseconds() const noexcept { return nanoseconds_; }

    /**
     * @brief Return the time point as microseconds
     * @note The decimal part, if any, will be discarded
     * @return constexpr Rep The value
     */
    constexpr Rep microseconds() const noexcept
    {
        return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000U));
    }

    /**
     * @brief Return the time point as milliseconds
     * @note The decimal part, if any, will be discarded
     * @return constexpr Rep The value
     */
    constexpr Rep milliseconds() const noexcept
    {
        return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000000U));
    }

    /**
     * @brief Return the time point as seconds
     * @note The decimal part, if any, will be discarded
     * @return constexpr Rep The value
     */
    constexpr Rep seconds() const noexcept
    {
        return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000000000U));
    }

    /**
     * @brief Increase operator.
     * @note No overflow protection
     * @param other Value to increase
     * @return constexpr TimePoint& The already increased object
     */
    constexpr TimePoint& operator+=(TimePoint const& other) noexcept
    {
        this->nanoseconds_ += other.nanoseconds_;
        return *this;
    }

    /**
     * @brief Decrease operator.
     * @note No underflow protection
     * @param other Value to decrease
     * @return constexpr TimePoint& The already decreased object
     */
    constexpr TimePoint& operator-=(TimePoint const& other) noexcept
    {
        this->nanoseconds_ -= other.nanoseconds_;
        return *this;
    }

private:
    Rep nanoseconds_;
};

constexpr TimePoint TimePoint_as_microseconds(mtps::u64 const micros) noexcept
{
    return TimePoint{micros * 1000U};
}

constexpr TimePoint TimePoint_as_miliseconds(mtps::u64 const millis) noexcept
{
    return TimePoint_as_microseconds(millis * 1000U);
}

constexpr TimePoint TimePoint_as_seconds(mtps::u32 const secs) noexcept
{
    return TimePoint_as_miliseconds(secs * 1000U);
}

constexpr TimePoint TimePoint_as_seconds(mtps::f32 const secs) noexcept
{
    return TimePoint_as_miliseconds(static_cast<mtps::u32>(secs * 1000U));
}

constexpr TimePoint operator+(const TimePoint& lhs,
                              const TimePoint& rhs) noexcept
{
    return {lhs.nanoseconds() + rhs.nanoseconds()};
}

constexpr TimePoint operator-(const TimePoint& lhs,
                              const TimePoint& rhs) noexcept
{
    return {lhs.nanoseconds() - rhs.nanoseconds()};
}

constexpr TimePoint operator*(const TimePoint& lhs,
                              const mtps::u64 scalar) noexcept
{
    return {lhs.nanoseconds() * scalar};
}

constexpr TimePoint operator*(const TimePoint& lhs,
                              const mtps::f32 scalar) noexcept
{
    return {static_cast<mtps::u64>(static_cast<mtps::f32>(lhs.nanoseconds()) *
                                   scalar)};
}

constexpr TimePoint operator/(const TimePoint& lhs,
                              const mtps::u64 scalar) noexcept
{
    return {static_cast<mtps::u64>(lhs.nanoseconds() / scalar)};
}

constexpr TimePoint operator/(const TimePoint& lhs,
                              const mtps::f32 scalar) noexcept
{
    return {static_cast<mtps::u64>(static_cast<mtps::f32>(lhs.nanoseconds()) /
                                   scalar)};
}

constexpr bool operator<(const TimePoint& lhs, const TimePoint& rhs) noexcept
{
    return {lhs.nanoseconds() < rhs.nanoseconds()};
}

constexpr bool operator>(const TimePoint& lhs, const TimePoint& rhs) noexcept
{
    return {lhs.nanoseconds() > rhs.nanoseconds()};
}

constexpr bool operator<=(const TimePoint& lhs, const TimePoint& rhs) noexcept
{
    return {lhs.nanoseconds() <= rhs.nanoseconds()};
}

constexpr bool operator>=(const TimePoint& lhs, const TimePoint& rhs) noexcept
{
    return {lhs.nanoseconds() >= rhs.nanoseconds()};
}

constexpr bool operator==(const TimePoint& lhs, const TimePoint& rhs) noexcept
{
    return {lhs.nanoseconds() == rhs.nanoseconds()};
}

constexpr bool operator!=(const TimePoint& lhs, const TimePoint& rhs) noexcept
{
    return {lhs.nanoseconds() != rhs.nanoseconds()};
}

constexpr mtps::str& operator<<(mtps::str& os, const TimePoint& tp) noexcept
{
    os << tp.nanoseconds();
    return os;
}
}  // namespace haf::time

#endif
