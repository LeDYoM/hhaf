#pragma once

#ifndef ZOPER_KEYMAPPING_HPP
#define ZOPER_KEYMAPPING_HPP

#include <mtypes/include/array.hpp>
#include <mtypes/include/object.hpp>
#include <haf/shareddata/include/ishareable.hpp>
#include <haf/input/include/key.hpp>

#include "gameplay/direction.hpp"

namespace zoper
{
class KeyMapping : public haf::shdata::IShareable
{
public:
    static constexpr mtps::fast_u16 TotalKeys = Direction::Total + 2U;

    KeyMapping();
    ~KeyMapping() override;

    void reset();

    haf::input::Key getKey(const Direction direction) const noexcept;
    Direction getDirectionFromKey(const haf::input::Key key) const noexcept;
    haf::input::Key getLaunchKey() const noexcept;
    bool isLaunchKey(const haf::input::Key key) const noexcept;
    haf::input::Key getPauseKey() const noexcept;
    bool isPauseKey(const haf::input::Key key) const noexcept;

    bool setKey(const mtps::u32 index, const haf::input::Key key);
    void apply();

    friend const mtps::Object &operator>>(const mtps::Object &obj, KeyMapping &key_mapping);
    friend mtps::Object &operator<<(mtps::Object &obj, const KeyMapping &key_mapping);

    bool serialize(mtps::Object&) const override;
    bool deserialize(mtps::Object const&) override;

private:
    mtps::array<haf::input::Key, KeyMapping::TotalKeys> m_keys;
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
