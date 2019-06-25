#pragma once

#ifndef LIB_TIMER_INCLUDE_HPP
#define LIB_TIMER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace lib
{
	class TimePoint
	{
	public:

		constexpr TimePoint(const u64 nanoseconds = 0U) noexcept
			: nanoseconds_{nanoseconds} {}

		constexpr u64 nanoseconds() const noexcept { return nanoseconds_; }
		constexpr u64 microseconds() const noexcept { return static_cast<u64>(nanoseconds_ / static_cast<u64>(1000U)); }
		constexpr u64 milliseconds() const noexcept { return static_cast<u64>(microseconds() / static_cast<u64>(1000U)); }
		constexpr u64 seconds() const noexcept { return static_cast<u64>(milliseconds() / static_cast<u64>(1000U)); }

        constexpr TimePoint& operator+=(const TimePoint& other) noexcept
        {
            this->nanoseconds_ += other.nanoseconds();
            return *this;
        } 

        constexpr TimePoint& operator-=(const TimePoint& other) noexcept
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

    constexpr TimePoint TimePoint_as_seconds(const u64 secs) noexcept
    {
        return TimePoint_as_miliseconds(secs * 1000U);
    }

	constexpr TimePoint operator+(const TimePoint& lhs, const TimePoint& rhs) noexcept
	{
		return { lhs.nanoseconds() + rhs.nanoseconds() };
	}

	constexpr TimePoint operator-(const TimePoint& lhs, const TimePoint& rhs) noexcept
	{
		return { lhs.nanoseconds() - rhs.nanoseconds() };
	}

	constexpr bool operator<(const TimePoint& lhs, const TimePoint& rhs) noexcept
	{
		return { lhs.nanoseconds() < rhs.nanoseconds() };
	}

	constexpr bool operator>(const TimePoint& lhs, const TimePoint& rhs) noexcept
	{
		return { lhs.nanoseconds() > rhs.nanoseconds() };
	}

	constexpr bool operator<=(const TimePoint& lhs, const TimePoint& rhs) noexcept
	{
		return { lhs.nanoseconds() <= rhs.nanoseconds() };
	}

	constexpr bool operator>=(const TimePoint& lhs, const TimePoint& rhs) noexcept
	{
		return { lhs.nanoseconds() >= rhs.nanoseconds() };
	}

	constexpr bool operator==(const TimePoint& lhs, const TimePoint& rhs) noexcept
	{
		return { lhs.nanoseconds() == rhs.nanoseconds() };
	}

	constexpr bool operator!=(const TimePoint& lhs, const TimePoint& rhs) noexcept
	{
		return { lhs.nanoseconds() != rhs.nanoseconds() };
	}

	constexpr str& operator<<(str & os, const TimePoint& tp) noexcept
	{
		os << tp.nanoseconds();
		return os;
	}
}

#endif
