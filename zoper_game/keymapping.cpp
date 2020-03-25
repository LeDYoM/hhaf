#include "keymapping.hpp"

using namespace lib;
using namespace mtps;

namespace zoper
{
    KeyMapping::KeyMapping() { reset(); }
    KeyMapping::~KeyMapping() = default;

    void KeyMapping::reset()
    {
        using namespace input;

        m_keys = { Key::Left, Key::Right, Key::Up, Key::Down, Key::Space, Key::Escape };
    }

    input::Key KeyMapping::getKey(const Direction d) const noexcept
    {
        return m_keys[d];
    }

    Direction KeyMapping::getDirectionFromKey(const input::Key key) const noexcept
    {
        for (u8 i = 0U; i < Direction::Total; ++i) {
            if (m_keys[i] == key)
            {
                return static_cast<Direction>(i);
            }
        }
        return Direction::DirectionData::Invalid;
    }

    input::Key KeyMapping::getLaunchKey() const noexcept
    {
        return m_keys[Direction::Total];
    }

    bool KeyMapping::isLaunchKey(const input::Key key) const noexcept
    {
        return key == getLaunchKey();
    }

    input::Key KeyMapping::getPauseKey() const noexcept
    {
        return m_keys[Direction::Total + 1];
    }

    bool KeyMapping::isPauseKey(const input::Key key) const noexcept
    {
        return key == getPauseKey();
    }

    bool KeyMapping::setKey(const u32 index, const input::Key key)
    {
        log_assert(index < TotalKeys, "Invalid index");

        for (u32 i{0U}; i < index; ++i) {
            if (m_keys[i] == key)
            {
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
            //			addConfigInt("key" + mtps::str(i), _keys[i],true);
        }

        //		addConfigInt("key_launch" + mtps::str(Direction::Total), _keys[Direction::Total]);
        //		addConfigInt("key_pause" + mtps::str(Direction::Total + 1), _keys[Direction::Total + 1]);
	}
}