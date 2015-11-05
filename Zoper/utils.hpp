#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <SFML/Window/Keyboard.hpp>
#include "lib/configuration.hpp"
#include <array>

namespace zoper
{
	enum Direction
	{
		Left = 0,
		Right = 1,
		Up = 2,
		Down = 3,
		Total = 4
	};

	class KeyMapping : public lib::Configuration
	{
	public:
		KeyMapping();
		virtual ~KeyMapping();

		void load();
		sf::Keyboard::Key getKey(Direction d) const;

		Direction getDirectionFromKey(sf::Keyboard::Key k) const;
	private:
		std::array<sf::Keyboard::Key,Direction::Total+1> _keys;
	};
}
#endif
