#ifndef __KEYMAPPING_HPP__
#define __KEYMAPPING_HPP__

#include <SFML/Window/Keyboard.hpp>
#include <lib/core/configuration.hpp>
#include "direction.hpp"
#include <array>

namespace zoper
{
	class KeyMapping : public lib::Configuration
	{
	public:
		KeyMapping();
		virtual ~KeyMapping();

		static const lib::u32 TotalKeys = Direction::Total + 2;

		sf::Keyboard::Key getKey(Direction d) const;
		Direction getDirectionFromKey(sf::Keyboard::Key k) const;
		sf::Keyboard::Key getLaunchKey() const;
		bool isLaunchKey(const sf::Keyboard::Key &key) const;
		sf::Keyboard::Key getPauseKey() const;
		bool isPauseKey(const sf::Keyboard::Key &key) const;

		bool setKey(lib::u32 index, sf::Keyboard::Key key);
		void apply();
	private:
		std::array<sf::Keyboard::Key, KeyMapping::TotalKeys> _keys;
	};
}

#endif
