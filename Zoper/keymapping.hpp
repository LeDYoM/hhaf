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

		sf::Keyboard::Key getKey(Direction d) const;
		Direction getDirectionFromKey(sf::Keyboard::Key k) const;
		sf::Keyboard::Key getLaunchKey() const;
		bool isLaunchKey(const sf::Keyboard::Key &key) const;
		sf::Keyboard::Key getPauseKey() const;
		bool isPauseKey(const sf::Keyboard::Key &key) const;
	private:
		std::array<sf::Keyboard::Key, Direction::Total + 2> _keys;
	};
}

#endif
