#include <lib/include/core/timer.hpp>
#include <chrono>

namespace lib
{
	typedef std::chrono::high_resolution_clock clock_t;
	static clock_t::time_point globalStart;

	struct TimerPrivate
	{
		clock_t::time_point start;
		std::chrono::microseconds pausedTime;
        
		TimerPrivate() :
            start{ clock_t::now() },
            pausedTime{ std::chrono::microseconds::zero() } {}
        ~TimerPrivate() = default;
	};

	Timer::Timer() : m_timerPrivate{ new TimerPrivate } {}

	Timer::~Timer() = default;
    Timer::Timer(Timer &&) = default;
    Timer & Timer::operator=(Timer &&) = default;

	TimePoint Timer::ellapsed() const
	{
        return TimePoint_as_microseconds((std::chrono::duration_cast<std::chrono::microseconds>
            (clock_t::now() - m_timerPrivate->start)).count());
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
		if (m_paused)
        {
			m_paused = false;
			m_pausedTime += m_pausedTimer.ellapsed();
		}
	}

	bool PausableTimer::switchPause()
	{
		m_paused ? resume() : pause();
		return m_paused;
	}

	TimePoint PausableTimer::ellapsed() const
	{
		TimePoint t{ Timer::ellapsed() - m_pausedTime };
		if (m_paused)
		{
			t -= m_pausedTimer.ellapsed();
		}
		return t;
	}

	void PausableTimer::restart()
	{
		m_pausedTime = TimePoint();
		m_paused = false;
		Timer::restart();
	}
}
