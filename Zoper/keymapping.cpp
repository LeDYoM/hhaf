#include "keymapping.hpp"

namespace zoper
{
	KeyMapping::KeyMapping() : lib::Configuration("config.cfg")
	{
		std::array<sf::Keyboard::Key, Direction::Total + 1> defaults{ sf::Keyboard::Key::Left,sf::Keyboard::Key::Right,sf::Keyboard::Key::Up,sf::Keyboard::Key::Down,sf::Keyboard::Key::Space };

		for (auto i = 0u; i < Direction::Total; ++i)
		{
			_keys[i] = static_cast<sf::Keyboard::Key>(addConfigInt("key" + std::to_string(i), defaults[i]));
		}

		_keys[Direction::Invalid] = static_cast<sf::Keyboard::Key>(addConfigInt("key" + std::to_string(Direction::Total), defaults[Direction::Total]));
	}

	KeyMapping::~KeyMapping()
	{
	}

	sf::Keyboard::Key KeyMapping::getKey(Direction d) const
	{
		return _keys[d];
	}
	Direction KeyMapping::getDirectionFromKey(sf::Keyboard::Key k) const
	{
		for (auto i = 0u; i < Direction::Total; ++i)
		{
			if (_keys[i] == k)
			{
				return Direction(static_cast<Direction>(i));
			}
		}
		return Direction::Invalid;
	}

	sf::Keyboard::Key KeyMapping::getLaunchKey() const
	{
		return _keys[Direction::Total];
	}

	bool KeyMapping::isLaunchKey(const sf::Keyboard::Key &key) const
	{
		return key == getLaunchKey();
	}

}
