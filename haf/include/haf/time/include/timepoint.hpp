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
class TimePoint final
{
public:
    using Rep = mtps::u64;  //<! Type to internally represent the data.

    TimePoint() noexcept;

    /**
     * @brief Constructor taking one parameter
     * @param nanoseconds Data to initialize the time point
     */
    explicit TimePoint(Rep nanoseconds) noexcept;

    /**
     * @brief Return the time point as nanoseconds
     * @return Rep The value
     */
    Rep nanoseconds() const noexcept;

    /**
     * @brief Return the time point as microseconds
     * @note The decimal part, if any, will be discarded
     * @return Rep The value
     */
    Rep microseconds() const noexcept;

    /**
     * @brief Return the time point as milliseconds
     * @note The decimal part, if any, will be discarded
     * @return Rep The value
     */
    Rep milliseconds() const noexcept;

    /**
     * @brief Return the time point as seconds
     * @note The decimal part, if any, will be discarded
     * @return Rep The value
     */
    Rep seconds() const noexcept;

    /**
     * @brief Return the time point as seconds in an mtps::f32 value
     * @return The value in mtps::32
     */
    mtps::f32 seconds_f32() const noexcept;

    /**
     * @brief Increase operator.
     * @note No overflow protection
     * @param other Value to increase
     * @return TimePoint& The already increased object
     */
    TimePoint& operator+=(TimePoint const& other) noexcept;

    /**
     * @brief Decrease operator.
     * @note No underflow protection
     * @param other Value to decrease
     * @return TimePoint& The already decreased object
     */
    TimePoint& operator-=(TimePoint const& other) noexcept;

    /**
     * @brief Multiplication operator.
     * @note No overflow protection
     * @param scalar Value to multiply
     * @return TimePoint& The already multiplied object
     */
    TimePoint& operator*=(mtps::f32 const scalar) noexcept;

    /**
     * @brief Multiplication operator.
     * @note No overflow protection
     * @note No division against zero protection
     * @param scalar Value to divide
     * @return TimePoint& The already divided object
     */
    TimePoint& operator/=(mtps::f32 const scalar) noexcept;

private:
    Rep nanoseconds_;  ///< Internal value representation
};

/**
 * @brief Add two time points
 * @param lhs First value
 * @param rhs Second value
 * @return Resulting TimePoint
 */
TimePoint operator+(TimePoint const& lhs, TimePoint const& rhs) noexcept;

/**
 * @brief Substract two time points
 * @param lhs First value
 * @param rhs Second value
 * @return Resulting TimePoint
 */
TimePoint operator-(TimePoint const& lhs, TimePoint const& rhs) noexcept;

/**
 * @brief Multiply one time point with an scalar
 * @param lhs First value
 * @param scalar Scalar value
 * @return Resulting TimePoint
 */
TimePoint operator*(TimePoint const& lhs, mtps::f32 const scalar) noexcept;

/**
 * @brief Divide one time point with an scalar
 * @param lhs First value
 * @param scalar Scalar value
 * @return Resulting TimePoint
 */
TimePoint operator/(TimePoint const& lhs, mtps::f32 const scalar) noexcept;

/**
 * @brief Create a TimePoint given an initial value in nanoseconds
 * @note This is the same behaviour as using the normal constructor
 * @param micros The initial value
 * @return TimePoint initialized to the correct value
 */
TimePoint TimePoint_as_nanoseconds(TimePoint::Rep const nanos) noexcept;

/**
 * @brief Create a TimePoint given an initial value in microseconds
 * @param micros The initial value
 * @return TimePoint initialized to the correct value
 */
TimePoint TimePoint_as_microseconds(TimePoint::Rep const micros) noexcept;

/**
 * @brief Create a TimePoint given an initial value in milliseconds
 * @param millis The initial value
 * @return TimePoint initialized to the correct value
 */
TimePoint TimePoint_as_miliseconds(TimePoint::Rep const millis) noexcept;

/**
 * @brief Create a TimePoint given an initial value in seconds
 * @param seconds The initial value
 * @return TimePoint initialized to the correct value
 */
TimePoint TimePoint_as_seconds(TimePoint::Rep const secs) noexcept;

/**
 * @brief Create a TimePoint given an initial value in seconds (f32 overload)
 * @param seconds The initial value
 * @return TimePoint initialized to the correct value
 */
TimePoint TimePoint_as_seconds_f32(mtps::f32 const secs) noexcept;

/**
 * @brief Lower than operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is lower than rhs
 * @return false lhs is not lower than rhs
 */
bool operator<(TimePoint const& lhs, TimePoint const& rhs) noexcept;

/**
 * @brief Higher than operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is higher than rhs
 * @return false lhs is not higher than rhs
 */
bool operator>(TimePoint const& lhs, TimePoint const& rhs) noexcept;

/**
 * @brief Lower or equal than operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is lower or equal than rhs
 * @return false lhs is not lower or equal than rhs
 */
bool operator<=(TimePoint const& lhs, TimePoint const& rhs) noexcept;

/**
 * @brief Higher or equal than operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is higher or equal than rhs
 * @return false lhs is not higher or equal than rhs
 */
bool operator>=(TimePoint const& lhs, TimePoint const& rhs) noexcept;

/**
 * @brief Equality operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is equal to rhs
 * @return false lhs is not equal to rhs
 */
bool operator==(TimePoint const& lhs, TimePoint const& rhs) noexcept;

/**
 * @brief Inequality operator
 * @param lhs First value
 * @param rhs Second value
 * @return true lhs is not equal to rhs
 * @return false lhs is not not equal to rhs
 */
bool operator!=(TimePoint const& lhs, TimePoint const& rhs) noexcept;

/**
 * @brief Output operator
 * @param os mtps::str where to perform the output
 * @param tp TimePoint to output
 * @return mtps::str& Reference to os with tp already output.
 */
mtps::str& operator<<(mtps::str& os, TimePoint const& tp);

}  // namespace haf::time

#endif
