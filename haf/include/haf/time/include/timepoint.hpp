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
    constexpr explicit TimePoint(Rep nanoseconds) noexcept :
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

    /**
     * @brief Multiplication operator.
     * @note No overflow protection
     * @param scalar Value to multiply
     * @return constexpr TimePoint& The already multiplied object
     */
    constexpr TimePoint& operator*=(mtps::f32 const scalar) noexcept
    {
        nanoseconds_ =
            static_cast<Rep>(static_cast<mtps::f32>(nanoseconds_ * scalar));
        return *this;
    }

    /**
     * @brief Multiplication operator.
     * @note No overflow protection
     * @note No division against zero protection
     * @param scalar Value to divide
     * @return constexpr TimePoint& The already divided object
     */
    constexpr TimePoint& operator/=(mtps::f32 const scalar) noexcept
    {
        nanoseconds_ =
            static_cast<Rep>(static_cast<mtps::f32>(nanoseconds_ / scalar));
        return *this;
    }

private:
    Rep nanoseconds_;  ///< Internal value representation
};

/**
 * @brief Add two time points
 * @param lhs First value
 * @param rhs Second value
 * @return constexpr Resulting TimePoint
 */
constexpr TimePoint operator+(TimePoint const& lhs,
                              TimePoint const& rhs) noexcept
{
    return TimePoint{lhs} += rhs;
}

/**
 * @brief Substract two time points
 * @param lhs First value
 * @param rhs Second value
 * @return constexpr Resulting TimePoint
 */
constexpr TimePoint operator-(TimePoint const& lhs,
                              TimePoint const& rhs) noexcept
{
    return TimePoint{lhs} -= rhs;
}

/**
 * @brief Multiply one time point with an scalar
 * @param lhs First value
 * @param scalar Scalar value
 * @return constexpr Resulting TimePoint
 */
constexpr TimePoint operator*(TimePoint const& lhs,
                              mtps::f32 const scalar) noexcept
{
    return TimePoint{lhs} *= scalar;
}

/**
 * @brief Divide one time point with an scalar
 * @param lhs First value
 * @param scalar Scalar value
 * @return constexpr Resulting TimePoint
 */
constexpr TimePoint operator/(TimePoint const& lhs,
                              mtps::f32 const scalar) noexcept
{
    return TimePoint{lhs} /= scalar;
}

/**
 * @brief Create a TimePoint given an initial value in nanoseconds
 * @note This is the same behaviour as using the normal constructor
 * @param micros The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_nanoseconds(mtps::u64 const nanos) noexcept
{
    return TimePoint{nanos};
}

/**
 * @brief Create a TimePoint given an initial value in microseconds
 * @param micros The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_microseconds(mtps::u64 const micros) noexcept
{
    return TimePoint{micros * 1000U};
}

/**
 * @brief Create a TimePoint given an initial value in milliseconds
 * @param millis The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_miliseconds(mtps::u64 const millis) noexcept
{
    return TimePoint_as_microseconds(millis * 1000U);
}

/**
 * @brief Create a TimePoint given an initial value in seconds
 * @param seconds The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_seconds(mtps::u32 const secs) noexcept
{
    return TimePoint_as_miliseconds(secs * 1000U);
}

/**
 * @brief Create a TimePoint given an initial value in seconds (f32 overload)
 * @param seconds The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_seconds(mtps::f32 const secs) noexcept
{
    return TimePoint_as_miliseconds(static_cast<mtps::u32>(secs * 1000U));
}

/**
 * @brief Lower than operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is lower than rhs
 * @return false lhs is not lower than rhs
 */
constexpr bool operator<(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return {lhs.nanoseconds() < rhs.nanoseconds()};
}

/**
 * @brief Higher than operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is higher than rhs
 * @return false lhs is not higher than rhs
 */
constexpr bool operator>(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return {lhs.nanoseconds() > rhs.nanoseconds()};
}

/**
 * @brief Lower or equal than operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is lower or equal than rhs
 * @return false lhs is not lower or equal than rhs
 */
constexpr bool operator<=(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return {lhs.nanoseconds() <= rhs.nanoseconds()};
}

/**
 * @brief Higher or equal than operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is higher or equal than rhs
 * @return false lhs is not higher or equal than rhs
 */
constexpr bool operator>=(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return {lhs.nanoseconds() >= rhs.nanoseconds()};
}

/**
 * @brief Equality operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is equal to rhs
 * @return false lhs is not equal to rhs
 */
constexpr bool operator==(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return lhs.nanoseconds() == rhs.nanoseconds();
}

/**
 * @brief Inequality operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is not equal to rhs
 * @return false lhs is not not equal to rhs
 */
constexpr bool operator!=(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return lhs.nanoseconds() != rhs.nanoseconds();
}

/**
 * @brief Output operator
 * @param os mtps::str where to perform the output
 * @param tp TimePoint to output
 * @return constexpr mtps::str& Reference to os with tp already output.
 */
constexpr mtps::str& operator<<(mtps::str& os, TimePoint const& tp) noexcept
{
    os << tp.nanoseconds();
    return os;
}
}  // namespace haf::time

#endif
