#ifndef __LIB_TIMER_HPP__
#define __LIB_TIMER_HPP__

#include <mtypes/include/types.hpp>

namespace lib
{
	struct TimerPrivate;
	struct TimePrivate;
	class Time
	{
	public:
		Time();
		Time(Time &&rh);
		~Time();
		Time &operator+=(const Time &rh);
		Time operator-(const Time &rh) const;
		Time &operator=(const Time &other);
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
}

#endif
