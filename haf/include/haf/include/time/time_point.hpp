#ifndef HAF_TIME_TIME_POINT_INCLUDE_HPP
#define HAF_TIME_TIME_POINT_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/types.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::time
{
/**
 * @brief Type representing a point in time.
 * It includes functions to convert and set different points in time.
 */
class HAF_API TimePoint final
{
public:
    using Rep = htps::u64;  //<! Type to internally represent the data.

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
     * @return Rep The value
     */
    constexpr Rep nanoseconds() const noexcept { return nanoseconds_; }

    /**
     * @brief Return the time point as microseconds
     * @note The decimal part, if any, will be discarded
     * @return Rep The value
     */
    constexpr Rep microseconds() const noexcept
    {
        return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000U));
    }

    /**
     * @brief Return the time point as milliseconds
     * @note The decimal part, if any, will be discarded
     * @return Rep The value
     */
    constexpr Rep milliseconds() const noexcept
    {
        return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000000U));
    }

    /**
     * @brief Return the time point as seconds
     * @note The decimal part, if any, will be discarded
     * @return Rep The value
     */
    constexpr Rep seconds() const noexcept
    {
        return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000000000U));
    }

    /**
     * @brief Return the time point as seconds in an htps::f32 value
     * @return The value in htps::32
     */
    constexpr htps::f32 seconds_f32() const noexcept
    {
        return static_cast<htps::f32>(static_cast<htps::f32>(nanoseconds_) /
                                      static_cast<htps::f32>(1000000000U));
    }

    /**
     * @brief Increase operator.
     * @note No overflow protection
     * @param other Value to increase
     * @return TimePoint& The already increased object
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
     * @return TimePoint& The already decreased object
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
     * @return TimePoint& The already multiplied object
     */
    constexpr TimePoint& operator*=(htps::f32 const scalar) noexcept
    {
        nanoseconds_ =
            static_cast<Rep>(static_cast<htps::f32>(nanoseconds_ * scalar));
        return *this;
    }

    /**
     * @brief Multiplication operator.
     * @note No overflow protection
     * @note No division against zero protection
     * @param scalar Value to divide
     * @return TimePoint& The already divided object
     */
    constexpr TimePoint& operator/=(htps::f32 const scalar) noexcept
    {
        nanoseconds_ =
            static_cast<Rep>(static_cast<htps::f32>(nanoseconds_ / scalar));
        return *this;
    }

private:
    Rep nanoseconds_;  ///< Internal value representation
};

/**
 * @brief Add two time points
 * @param lhs First value
 * @param rhs Second value
 * @return Resulting TimePoint
 */
constexpr TimePoint operator+(TimePoint const& lhs,
                              TimePoint const& rhs) noexcept
{
    return TimePoint{lhs.nanoseconds()} += rhs;
}

/**
 * @brief Substract two time points
 * @param lhs First value
 * @param rhs Second value
 * @return Resulting TimePoint
 */
constexpr TimePoint operator-(TimePoint const& lhs,
                              TimePoint const& rhs) noexcept
{
    return TimePoint{lhs.nanoseconds()} -= rhs;
}

/**
 * @brief Multiply one time point with an scalar
 * @param lhs First value
 * @param scalar Scalar value
 * @return Resulting TimePoint
 */
constexpr TimePoint operator*(TimePoint const& lhs, htps::f32 const scalar) noexcept
{
    return TimePoint{lhs.nanoseconds()} *= scalar;
}

/**
 * @brief Divide one time point with an scalar
 * @param lhs First value
 * @param scalar Scalar value
 * @return Resulting TimePoint
 */
constexpr TimePoint operator/(TimePoint const& lhs, htps::f32 const scalar) noexcept
{
    return TimePoint{lhs.nanoseconds()} /= scalar;
}


/**
 * @brief Create a TimePoint given an initial value in nanoseconds
 * @note This is the same behaviour as using the normal constructor
 * @param micros The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_nanoseconds(TimePoint::Rep const nanos) noexcept
{
    return TimePoint{nanos};
}

/**
 * @brief Create a TimePoint given an initial value in microseconds
 * @param micros The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_microseconds(TimePoint::Rep const micros) noexcept
{
    return TimePoint{micros * 1000U};
}

/**
 * @brief Create a TimePoint given an initial value in milliseconds
 * @param millis The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_miliseconds(TimePoint::Rep const millis) noexcept
{
    return TimePoint_as_microseconds(millis * 1000U);
}

/**
 * @brief Create a TimePoint given an initial value in seconds
 * @param seconds The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_seconds(TimePoint::Rep const secs) noexcept
{
    return TimePoint_as_miliseconds(secs * 1000U);
}

/**
 * @brief Create a TimePoint given an initial value in seconds (f32 overload)
 * @param seconds The initial value
 * @return TimePoint initialized to the correct value
 */
constexpr TimePoint TimePoint_as_seconds_f32(htps::f32 const secs) noexcept
{
    return TimePoint_as_miliseconds(static_cast<TimePoint::Rep>(secs * 1000U));
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
    return lhs.nanoseconds() >= rhs.nanoseconds();
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
 * @param os htps::str where to perform the output
 * @param tp TimePoint to output
 * @return htps::str& Reference to os with tp already output.
 */
constexpr htps::str& operator<<(htps::str& os, TimePoint const& tp)
{
    os << tp.nanoseconds();
    return os;
}

}  // namespace haf::time

#endif
