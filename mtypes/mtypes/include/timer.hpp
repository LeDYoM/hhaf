#pragma once

#ifndef LIB_TIMER_INCLUDE_HPP__
#define LIB_TIMER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include "mtypes_export.hpp"

namespace lib
{
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

    struct TimerConnection
    {
        Time period;
        Time lastCheck;
        emitter<Time> TimerEmitter;
    };

	class TimerTrigger
	{
	public:
		TimerTrigger(Timer& timer) : m_internalTimer{ timer } {}

        template <typename T>
        void addConnection(Time period, T&& callback) {
            m_timerConnections.emplace_back(
                std::move(period),
                m_internalTimer.getElapsedTime(),
                std::forward<T>(callback));
        }
	private:
		Timer & m_internalTimer;
        vector<TimerConnection> m_timerConnections;
	};
}

#endif
