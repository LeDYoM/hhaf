#pragma once

#ifndef ZOPER_KEYMAPPING_HPP
#define ZOPER_KEYMAPPING_HPP

#include <mtypes/include/array.hpp>
#include <mtypes/include/object.hpp>

#include <lib/include/key.hpp>

#include "gameplay/direction.hpp"

namespace zoper
{
class KeyMapping
{
public:
    static constexpr lib::u32 TotalKeys = Direction::Total + 2;

    KeyMapping();
    virtual ~KeyMapping();

    void reset();

    lib::Key getKey(const Direction direction) const noexcept;
    Direction getDirectionFromKey(const lib::Key key) const noexcept;
    lib::Key getLaunchKey() const noexcept;
    bool isLaunchKey(const lib::Key key) const noexcept;
    lib::Key getPauseKey() const noexcept;
    bool isPauseKey(const lib::Key key) const noexcept;

    bool setKey(const lib::u32 index, const lib::Key key);
    void apply();

    friend const lib::Object &operator>>(const lib::Object &obj, KeyMapping &key_mapping);
    friend lib::Object &operator<<(lib::Object &obj, const KeyMapping &key_mapping);

private:
    lib::array<lib::Key, KeyMapping::TotalKeys> m_keys;
};

inline const lib::Object &operator>>(const lib::Object &obj, KeyMapping &key_mapping)
{
    obj["keys"].getObject() >> key_mapping.m_keys;
    return obj;
}

inline Object &operator<<(Object &obj, const KeyMapping &key_mapping)
{
    obj.set("keys", key_mapping.m_keys);
    return obj;
}
} // namespace zoper

#endif
