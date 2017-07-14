#include "keymapping.hpp"

namespace zoper
{
	KeyMapping::KeyMapping() : lib::IUserProperties("config.cfg") {}
	KeyMapping::~KeyMapping() = default;

	void KeyMapping::setProperties(lib::Configuration & config)
	{
		using namespace lib;
		using namespace lib::input;

		std::array<lib::input::Key, TotalKeys> defaults{ Key::Left, Key::Right, Key::Up, Key::Down, Key::Space, Key::Escape };

		for (auto i = 0u; i < Direction::Total; ++i) {
			m_keys[i] = config.registerProperty("key" + str(i),defaults[i]);
		}

		m_keys[Direction::Total] = config.registerProperty("key_launch", defaults[Direction::Total]);
		m_keys[Direction::Total + 1] = config.registerProperty("key_pause", defaults[Direction::Total+1]);
	}

	lib::input::Key KeyMapping::getKey(const Direction d) const noexcept
	{
		return m_keys[d];
	}

	Direction KeyMapping::getDirectionFromKey(const lib::input::Key k) const noexcept
	{
		for (lib::u8 i{ 0 }; i < Direction::Total; ++i) {
			if (m_keys[i] == k) {
				return static_cast<Direction>(i);
			}
		}
		return Direction::Invalid;
	}

	lib::input::Key KeyMapping::getLaunchKey() const noexcept
	{
		return m_keys[Direction::Total];
	}

	bool KeyMapping::isLaunchKey(const lib::input::Key key) const noexcept
	{
		return key == getLaunchKey();
	}

	lib::input::Key KeyMapping::getPauseKey() const noexcept
	{
		return m_keys[Direction::Total + 1];
	}

	bool KeyMapping::isPauseKey(const lib::input::Key key) const noexcept
	{
		return key == getPauseKey();
	}

	bool KeyMapping::setKey(const lib::u32 index, const lib::input::Key key)
	{
		CLIENT_ASSERT(index < TotalKeys, "Invalid index");

		for (lib::u32 i = 0u; i < index; ++i) {
			if (m_keys[i] == key) {
				return false;
			}
		}
		m_keys[index] = key;
		return true;
	}

	void KeyMapping::apply()
	{
		for (auto i = 0u; i < Direction::Total; ++i)
		{
			//			addConfigInt("key" + str(i), _keys[i],true);
		}

		//		addConfigInt("key_launch" + str(Direction::Total), _keys[Direction::Total]);
		//		addConfigInt("key_pause" + str(Direction::Total + 1), _keys[Direction::Total + 1]);
	}
}