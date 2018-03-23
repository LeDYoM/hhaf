#pragma once

#ifndef LIB_TIMER_INCLUDE_HPP__
#define LIB_TIMER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include "mtypes_export.hpp"
#include <chrono>

namespace lib
{
    namespace time
    {
        class TimePoint
        {
        public:
            using time_rep_t = s64;
            using millis_rep_t = s64;
            using seconds_rep_t = f32;

            constexpr TimePoint(time_rep_t representation)
                : m_representation{ representation } {}
            
            constexpr time_rep_t micro() const noexcept {
                return m_representation;
            }

            constexpr millis_rep_t millis() const noexcept {
                return static_cast<millis_rep_t>(m_representation / 1000);
            }

            constexpr seconds_rep_t seconds() const noexcept {
                return static_cast<seconds_rep_t>(millis() / 1000);
            }

            friend constexpr TimePoint operator-(const TimePoint &lhs, const TimePoint &rhs) noexcept;
            friend constexpr bool operator>(const TimePoint &lhs, const TimePoint &rhs) noexcept;
            friend constexpr bool operator<(const TimePoint &lhs, const TimePoint &rhs) noexcept;
            friend constexpr bool operator==(const TimePoint &lhs, const TimePoint &rhs) noexcept;
            friend constexpr bool operator!=(const TimePoint &lhs, const TimePoint &rhs) noexcept;

        private:
            time_rep_t m_representation;
        };

        constexpr TimePoint operator-(const TimePoint &lhs, const TimePoint &rhs) noexcept {
            return TimePoint(lhs.m_representation - rhs.m_representation);
        }

        constexpr bool operator>(const TimePoint &lhs, const TimePoint &rhs) noexcept {
            return lhs.m_representation > rhs.m_representation;
        }

        constexpr bool operator<(const TimePoint &lhs, const TimePoint &rhs) noexcept {
            return lhs.m_representation < rhs.m_representation;
        }

        constexpr bool operator==(const TimePoint &lhs, const TimePoint &rhs) noexcept {
            return lhs.m_representation == rhs.m_representation;
        }

        constexpr bool operator!=(const TimePoint &lhs, const TimePoint &rhs) noexcept {
            return lhs.m_representation != rhs.m_representation;
        }

        class MTYPES_EXPORT Clock
        {
        public:
            TimePoint now() const;
        };
    }

	struct TimerPrivate;
	struct TimePrivate;

	class MTYPES_EXPORT Time
	{
	public:
		Time();
		Time(Time &&rh);
		Time&operator=(Time&&rhs);
		Time(const Time&rhs);
		Time &operator=(const Time&rhs);
		~Time();

		Time &operator+=(const Time &rh);
		Time &operator-=(const Time &rh);

		Time operator-(const Time &rh) const;
		u64 asMicroSeconds() const;
		u64 asMilliSeconds() const;
		u64 asSeconds() const;
		void setZero();

	private:
#ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable:4251)
#endif
		uptr<TimePrivate> m_timePrivate;
#ifdef _MSC_VER
        #pragma warning(pop)
#endif
		friend class Timer;
	};
	class MTYPES_EXPORT Timer
	{
	public:
		Timer();
		virtual ~Timer();

		virtual const Time getElapsedTime() const;
		virtual void restart();
        void setAcceleration(f32 accel);
	private:
#ifdef _MSC_VER
        #pragma warning(push)
        #pragma warning(disable:4251)
#endif
        uptr<TimerPrivate> m_timerPrivate;
#ifdef _MSC_VER
        #pragma warning(pop)
#endif
	};

	class MTYPES_EXPORT PausableTimer : public Timer
	{
	public:
		void pause();
		void resume();
		bool switchPause();
		virtual const Time getElapsedTime() const override;
		virtual void restart() override;

	private:
		Timer m_pausedTimer;
		Time m_pausedTime;
		bool m_paused{ false };
	};
}

#endif
