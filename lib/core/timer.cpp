#include "timer.hpp"
#include <chrono>

namespace lib
{
	typedef std::chrono::high_resolution_clock clock_t;
	static clock_t::time_point globalStart;

	struct TimePrivate
	{
		std::chrono::microseconds m_micrseconds;
		TimePrivate(std::chrono::microseconds microseconds)
			: m_micrseconds{microseconds} {}

		TimePrivate(TimePrivate &&rh) = default;
	};

	Time::Time()
		: m_timePrivate{ std::make_unique<TimePrivate>(std::chrono::microseconds::zero()) } { }

	Time::Time(Time &&rh)
	{
		m_timePrivate = std::move(rh.m_timePrivate);
	}

	Time::~Time() = default;

	Time &Time::operator+=(const Time &rh)
	{
		m_timePrivate->m_micrseconds += rh.m_timePrivate->m_micrseconds;
		return *this;
	}

	Time Time::operator-(const Time &rh) const
	{
		Time t;
		t.m_timePrivate = std::make_unique<TimePrivate>(this->m_timePrivate->m_micrseconds - rh.m_timePrivate->m_micrseconds);
		return t;
	}

	Time & Time::operator=(const Time &other)
	{
		m_timePrivate->m_micrseconds = other.m_timePrivate->m_micrseconds;
		return *this;
	}

	u64 Time::asMicroSeconds() const
	{
		return m_timePrivate->m_micrseconds.count();
	}

	u64 Time::asMilliSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_timePrivate->m_micrseconds).count();
	}

	u64 Time::asSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::seconds>(m_timePrivate->m_micrseconds).count();
	}

	void Time::setZero()
	{
		if (m_timePrivate)
			m_timePrivate->m_micrseconds = std::chrono::microseconds::zero();
	}

	struct TimerPrivate
	{

		clock_t::time_point start;
		std::chrono::microseconds pausedTime;
		TimerPrivate()
		{
			start = clock_t::now();
			pausedTime = std::chrono::microseconds::zero();
		}
	};

	Timer::Timer() : m_timerPrivate{ new TimerPrivate } {}

	Timer::~Timer() = default;

	const Time Timer::getElapsedTime() const
	{
		std::chrono::microseconds ellapsed = std::chrono::duration_cast<std::chrono::microseconds>(clock_t::now() - m_timerPrivate->start);
		Time t;
		t.m_timePrivate = std::make_unique<TimePrivate>(ellapsed);
		return t;
	}

	void Timer::restart()
	{
		m_timerPrivate->start = clock_t::now();
	}

	void PausableTimer::pause()
	{
		if (!m_paused)
		{
			m_paused = true;
			m_pausedTimer.restart();
		}
	}

	void PausableTimer::resume()
	{
		if (m_paused) {
			m_paused = false;
			m_pausedTime += m_pausedTimer.getElapsedTime();
		}
	}

	bool PausableTimer::switchPause()
	{
		m_paused ? resume() : pause();
		return m_paused;
	}

	const Time PausableTimer::getElapsedTime() const
	{
		Time t = (Timer::getElapsedTime() - m_pausedTime);
		if (m_paused)
			t = t - m_pausedTimer.getElapsedTime();
		return t;
	}

	void PausableTimer::restart()
	{
		m_pausedTime.setZero();
		m_paused = false;
		Timer::restart();
	}
}
