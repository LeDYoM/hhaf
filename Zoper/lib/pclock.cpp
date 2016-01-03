#include "pclock.hpp"

namespace lib
{
	PClock::PClock()
	{
	}


	PClock::~PClock()
	{
	}

	void PClock::pause()
	{

		if (!_paused)
		{
			_paused = true;
			_pauseClock.restart();
		}

	}

	void PClock::start()
	{

		if (_paused)
		{
			_paused = false;
			_pausedTime += _pauseClock.getElapsedTime();
		}

	}

	const sf::Time PClock::getElapsedTime()
	{
		return _clock.getElapsedTime() - _pausedTime;
	}

	sf::Time PClock::restart()
	{
		sf::Time current{ getElapsedTime() };
		_pausedTime = sf::Time::Zero;
		_paused = false;
		_clock.restart();

		return current;
	}
}
