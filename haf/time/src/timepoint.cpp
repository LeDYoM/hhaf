#include <haf/time/include/timepoint.hpp>

namespace haf::time
{
TimePoint::TimePoint() noexcept : nanoseconds_{Rep{0U}}
{}

TimePoint::TimePoint(TimePoint::Rep nanoseconds) noexcept :
    nanoseconds_{std::move(nanoseconds)}
{}

TimePoint::Rep TimePoint::nanoseconds() const noexcept
{
    return nanoseconds_;
}

TimePoint::Rep TimePoint::microseconds() const noexcept
{
    return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000U));
}

TimePoint::Rep TimePoint::milliseconds() const noexcept
{
    return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000000U));
}

TimePoint::Rep TimePoint::seconds() const noexcept
{
    return static_cast<Rep>(nanoseconds_ / static_cast<Rep>(1000000000U));
}

mtps::f32 TimePoint::seconds_f32() const noexcept
{
    return static_cast<mtps::f32>(static_cast<mtps::f32>(nanoseconds_) /
                                  static_cast<mtps::f32>(1000000000U));
}

TimePoint& TimePoint::operator+=(TimePoint const& other) noexcept
{
    this->nanoseconds_ += other.nanoseconds_;
    return *this;
}

TimePoint& TimePoint::operator-=(TimePoint const& other) noexcept
{
    this->nanoseconds_ -= other.nanoseconds_;
    return *this;
}

TimePoint& TimePoint::operator*=(mtps::f32 const scalar) noexcept
{
    nanoseconds_ =
        static_cast<Rep>(static_cast<mtps::f32>(nanoseconds_ * scalar));
    return *this;
}

TimePoint& TimePoint::operator/=(mtps::f32 const scalar) noexcept
{
    nanoseconds_ =
        static_cast<Rep>(static_cast<mtps::f32>(nanoseconds_ / scalar));
    return *this;
}

TimePoint operator+(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return TimePoint{lhs.nanoseconds()} += rhs;
}

TimePoint operator-(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return TimePoint{lhs.nanoseconds()} -= rhs;
}

TimePoint operator*(TimePoint const& lhs, mtps::f32 const scalar) noexcept
{
    return TimePoint{lhs.nanoseconds()} *= scalar;
}

TimePoint operator/(TimePoint const& lhs, mtps::f32 const scalar) noexcept
{
    return TimePoint{lhs.nanoseconds()} /= scalar;
}

TimePoint TimePoint_as_nanoseconds(TimePoint::Rep const nanos) noexcept
{
    return TimePoint{nanos};
}

TimePoint TimePoint_as_microseconds(TimePoint::Rep const micros) noexcept
{
    return TimePoint{micros * 1000U};
}

TimePoint TimePoint_as_miliseconds(TimePoint::Rep const millis) noexcept
{
    return TimePoint_as_microseconds(millis * 1000U);
}

TimePoint TimePoint_as_seconds(TimePoint::Rep const secs) noexcept
{
    return TimePoint_as_miliseconds(secs * 1000U);
}

TimePoint TimePoint_as_seconds_f32(mtps::f32 const secs) noexcept
{
    return TimePoint_as_miliseconds(static_cast<TimePoint::Rep>(secs * 1000U));
}

bool operator<(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return {lhs.nanoseconds() < rhs.nanoseconds()};
}

bool operator>(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return {lhs.nanoseconds() > rhs.nanoseconds()};
}

bool operator<=(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return {lhs.nanoseconds() <= rhs.nanoseconds()};
}

bool operator>=(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return {lhs.nanoseconds() >= rhs.nanoseconds()};
}

bool operator==(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return lhs.nanoseconds() == rhs.nanoseconds();
}

bool operator!=(TimePoint const& lhs, TimePoint const& rhs) noexcept
{
    return lhs.nanoseconds() != rhs.nanoseconds();
}

mtps::str& operator<<(mtps::str& os, TimePoint const& tp)
{
    os << tp.nanoseconds();
    return os;
}
}  // namespace haf::time
