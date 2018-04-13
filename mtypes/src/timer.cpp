#include "../mtypes/include/timer.hpp"
#include <chrono>

namespace lib
{
	typedef std::chrono::high_resolution_clock clock_t;
	static clock_t::time_point globalStart;

	struct TimePrivate
	{
		std::chrono::microseconds m_microseconds;
		TimePrivate(std::chrono::microseconds microseconds)
			: m_microseconds{microseconds} {}

		TimePrivate(TimePrivate &&) = default;
		TimePrivate(const TimePrivate &) = default;
		TimePrivate&operator=(TimePrivate &&) = default;
		TimePrivate&operator=(const TimePrivate &) = default;
	};

	Time::Time()
		: m_timePrivate{ muptr<TimePrivate>(std::chrono::microseconds::zero()) } { }

	Time::Time(Time &&rh)
	{
		m_timePrivate = std::move(rh.m_timePrivate);
	}

	Time::Time(const Time & rhs) : m_timePrivate{ muptr<TimePrivate>(*(rhs.m_timePrivate)) } { }

	Time & Time::operator=(const Time &rhs)
	{
		this->m_timePrivate.reset(new TimePrivate(*(rhs.m_timePrivate)));
		return *this;
	}

	Time & Time::operator=(Time && rhs)
	{
		std::swap(this->m_timePrivate, rhs.m_timePrivate);
		return *this;
	}

	Time::~Time() = default;

	Time &Time::operator+=(const Time &rh)
	{
		m_timePrivate->m_microseconds += rh.m_timePrivate->m_microseconds;
		return *this;
	}

	Time & Time::operator-=(const Time & rh)
	{
		m_timePrivate->m_microseconds -= rh.m_timePrivate->m_microseconds;
		return *this;
	}

	Time Time::operator-(const Time &rh) const
	{
		Time t(*this);
		t -= rh;
        return t;
	}

	u64 Time::asMicroSeconds() const
	{
		return m_timePrivate->m_microseconds.count();
	}

	u64 Time::asMilliSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(m_timePrivate->m_microseconds).count();
	}

	u64 Time::asSeconds() const
	{
		return std::chrono::duration_cast<std::chrono::seconds>(m_timePrivate->m_microseconds).count();
	}

	void Time::setZero()
	{
		m_timePrivate->m_microseconds = std::chrono::microseconds::zero();
	}

	struct TimerPrivate
	{
		clock_t::time_point start;
		std::chrono::microseconds pausedTime;
        f32 acceleration;
        
		TimerPrivate() :
            start{ clock_t::now() },
            pausedTime{ std::chrono::microseconds::zero() },
            acceleration{ 1.0f }
        {}
	};

	Timer::Timer() : m_timerPrivate{ new TimerPrivate } {}

	Timer::~Timer() = default;

	const Time Timer::getElapsedTime() const
	{
		Time t;
		*(t.m_timePrivate) = std::chrono::duration_cast<std::chrono::microseconds>(clock_t::now() - m_timerPrivate->start);
		return t;
	}

	void Timer::restart()
	{
		m_timerPrivate->start = clock_t::now();
	}

	void PausableTimer::pause()
	{
		if (!m_paused) {
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
		Time t{ Timer::getElapsedTime() - m_pausedTime };
		if (m_paused)
		{
			t -= m_pausedTimer.getElapsedTime();
		}
		return t;
	}

	void PausableTimer::restart()
	{
		m_pausedTime.setZero();
		m_paused = false;
		Timer::restart();
	}
}
