#ifndef __LIB_PCLOCK_HPP__
#define __LIB_PCLOCK_HPP__

#include <SFML/System.hpp>

namespace lib
{
	class PClock
	{
	public:
		PClock();
		virtual ~PClock();

		void pause();
		void start();
		const sf::Time getElapsedTime();
		sf::Time restart();

	private:
		bool _paused;
		sf::Clock _clock;
		sf::Clock _pauseClock;
		sf::Time _pausedTime{ sf::Time::Zero };
	};
}

#endif