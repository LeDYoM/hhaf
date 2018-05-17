#pragma once

#ifndef LIB_TIMER_INCLUDE_HPP__
#define LIB_TIMER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/include/lib.hpp>

namespace lib
{
	struct TimerPrivate;
	struct TimePrivate;

    enum class TimeInitializationTag
    {
        Microseconds,
        Milliseconds,
        Seconds
    };

	class LIB_API_EXPORT Time final
	{
	public:
        explicit Time(const u64 quantity = 0, TimeInitializationTag initTag = TimeInitializationTag::Microseconds);
		Time(Time &&rh) noexcept;
        Time(const Time&rhs);
        Time&operator=(Time&&rhs) noexcept;
		Time&operator=(const Time&rhs);
		~Time();

		Time &operator+=(const Time &rh);
		Time &operator-=(const Time &rh);
		Time operator-(const Time &rh) const;
        bool operator>(const Time&rhs) const noexcept;
        bool operator<(const Time&rhs) const noexcept;
        bool operator>=(const Time&rhs) const noexcept;
        bool operator<=(const Time&rhs) const noexcept;
        bool operator==(const Time&rhs) const noexcept;
        bool operator!=(const Time&rhs) const noexcept;

        u64 asMicroSeconds() const noexcept;
        u64 asMilliSeconds() const noexcept;
        u64 asSeconds() const noexcept;
        void setZero() noexcept;

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
	class LIB_API_EXPORT Timer
	{
	public:
		Timer();
		virtual ~Timer();

        Timer(Timer&&) = default;
        Timer& operator=(Timer&&) = default;

		virtual Time getElapsedTime() const;
		virtual void restart();
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

	class LIB_API_EXPORT PausableTimer : public Timer
	{
	public:
		void pause();
		void resume();
		bool switchPause();
		virtual Time getElapsedTime() const override;
		virtual void restart() override;

	private:
		Timer m_pausedTimer;
		Time m_pausedTime;
		bool m_paused{ false };
	};

    inline Time TimeFromMillis(const u64 millis) noexcept {
        return Time{ millis, TimeInitializationTag::Milliseconds };
    }

}

#endif
