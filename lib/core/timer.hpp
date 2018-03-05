#ifndef __LIB_TIMER_HPP__
#define __LIB_TIMER_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>

namespace lib
{
	struct TimerPrivate;
	struct TimePrivate;

	class Time
	{
	public:
		Time();
		Time(Time &&rh);
		Time&operator=(Time&&rhs);
		explicit Time(const Time&rhs);
		Time &operator=(const Time&rhs);
		~Time();
		Time &operator+=(const Time &rh);
		Time operator-(const Time &rh) const;
		u64 asMicroSeconds() const;
		u64 asMilliSeconds() const;
		u64 asSeconds() const;
		void setZero();

	private:
		uptr<TimePrivate> m_timePrivate;
		friend class Timer;
	};
	class Timer
	{
	public:
		Timer();
		virtual ~Timer();

		virtual const Time getElapsedTime() const;
		virtual void restart();
	private:
		uptr<TimerPrivate> m_timerPrivate;
	};

	class PausableTimer : public Timer
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

	/*
	class TimerTrigger
	{
	public:
		TimerTrigger(Timer& timer) : m_internalTimer{ timer } {}
		emitter<Time>
	private:
		Timer & m_internalTimer;
	};
	*/
}

#endif
