#ifndef __KEYMAPPING_HPP__
#define __KEYMAPPING_HPP__

#include <SFML/Window/Keyboard.hpp>
#include "lib/configuration.hpp"
#include "direction.hpp"
#include <array>

namespace zoper
{
	class KeyMapping : public lib::Configuration
	{
	public:
		KeyMapping();
		virtual ~KeyMapping();

		void load();
		sf::Keyboard::Key getKey(Direction d) const;

		Direction getDirectionFromKey(sf::Keyboard::Key k) const;
	private:
		std::array<sf::Keyboard::Key, Direction::Total + 1> _keys;
	};
}

#endif
