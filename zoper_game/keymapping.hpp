#pragma once

#ifndef ZOPER_KEYMAPPING_HPP
#define ZOPER_KEYMAPPING_HPP

#include <mtypes/include/array.hpp>
#include <mtypes/include/object.hpp>

#include <lib/input/include/key.hpp>

#include "gameplay/direction.hpp"

namespace zoper
{
class KeyMapping
{
public:
    static constexpr mtps::u32 TotalKeys = Direction::Total + 2;

    KeyMapping();
    virtual ~KeyMapping();

    void reset();

    lib::input::Key getKey(const Direction direction) const noexcept;
    Direction getDirectionFromKey(const lib::input::Key key) const noexcept;
    lib::input::Key getLaunchKey() const noexcept;
    bool isLaunchKey(const lib::input::Key key) const noexcept;
    lib::input::Key getPauseKey() const noexcept;
    bool isPauseKey(const lib::input::Key key) const noexcept;

    bool setKey(const mtps::u32 index, const lib::input::Key key);
    void apply();

    friend const mtps::Object &operator>>(const mtps::Object &obj, KeyMapping &key_mapping);
    friend mtps::Object &operator<<(mtps::Object &obj, const KeyMapping &key_mapping);

private:
    mtps::array<lib::input::Key, KeyMapping::TotalKeys> m_keys;
};

inline const mtps::Object &operator>>(const mtps::Object &obj, KeyMapping &key_mapping)
{
    obj["keys"].getObject() >> key_mapping.m_keys;
    return obj;
}

inline mtps::Object &operator<<(mtps::Object &obj, const KeyMapping &key_mapping)
{
    obj.set("keys", key_mapping.m_keys);
    return obj;
}
} // namespace zoper

#endif
