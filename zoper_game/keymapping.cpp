#include "keymapping.hpp"
#include <hlog/include/hlog.hpp>

using namespace haf;
using namespace htps;

namespace zoper
{
KeyMapping::KeyMapping()
{
    reset();
}
KeyMapping::~KeyMapping() = default;

void KeyMapping::reset()
{
    using namespace input;

    keys_ = {Key::Left, Key::Right, Key::Up,
              Key::Down, Key::Space, Key::Escape};
}

input::Key KeyMapping::getKey(const Direction d) const noexcept
{
    return keys_[static_cast<size_type>(d.value())];
}

Direction KeyMapping::getDirectionFromKey(const input::Key key) const noexcept
{
    for (fast_u8 i{0U}; i < Direction::Total; ++i)
    {
        if (keys_[i] == key)
        {
            return static_cast<Direction::DirectionData>(i);
        }
    }
    return Direction::DirectionData::Invalid;
}

input::Key KeyMapping::getLaunchKey() const noexcept
{
    return keys_[Direction::Total];
}

bool KeyMapping::isLaunchKey(const input::Key key) const noexcept
{
    return key == getLaunchKey();
}

input::Key KeyMapping::getPauseKey() const noexcept
{
    return keys_[Direction::Total + 1];
}

bool KeyMapping::isPauseKey(const input::Key key) const noexcept
{
    return key == getPauseKey();
}

bool KeyMapping::setKey(const u32 index, const input::Key key)
{
    LogAsserter::log_assert(index < TotalKeys, "Invalid index");

    for (u32 i{0U}; i < index; ++i)
    {
        if (keys_[i] == key)
        {
            return false;
        }
    }
    keys_[index] = key;
    return true;
}

bool KeyMapping::serialize(htps::Object& obj) const
{
    obj.set("keys", keys_);
    return true;
}

bool KeyMapping::deserialize(htps::Object const& obj)
{
    obj["keys"].getObject() >> keys_;
    return true;
}

void KeyMapping::apply()
{
    for (auto i = 0u; i < Direction::Total; ++i)
    {
        // addConfigInt("key" + str(i), _keys[i],true);
    }

    //  addConfigInt("key_launch" + str(Direction::Total),
    //_keys[Direction::Total]); 		addConfigInt("key_pause" +
    //str(Direction::Total
    //+ 1), _keys[Direction::Total + 1]);
}
}  // namespace zoper