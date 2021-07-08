#ifndef ZOPER_KEYMAPPING_HPP
#define ZOPER_KEYMAPPING_HPP

#include <htypes/include/array.hpp>
#include <htypes/include/object.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/input/key.hpp>

#include "gameplay/direction.hpp"

namespace zoper
{
class KeyMapping : public haf::shdata::IShareable
{
public:
    static constexpr htps::fast_u16 TotalKeys = Direction::Total + 2U;

    KeyMapping();
    ~KeyMapping() override;

    void reset();

    haf::input::Key getKey(const Direction direction) const noexcept;
    Direction getDirectionFromKey(const haf::input::Key key) const noexcept;
    haf::input::Key getLaunchKey() const noexcept;
    bool isLaunchKey(const haf::input::Key key) const noexcept;
    haf::input::Key getPauseKey() const noexcept;
    bool isPauseKey(const haf::input::Key key) const noexcept;

    bool setKey(const htps::u32 index, const haf::input::Key key);
    void apply();

    friend const htps::Object& operator>>(const htps::Object& obj,
                                          KeyMapping& key_mapping);
    friend htps::Object& operator<<(htps::Object& obj,
                                    const KeyMapping& key_mapping);

    bool serialize(htps::Object&) const override;
    bool deserialize(htps::Object const&) override;

private:
    htps::array<haf::input::Key, KeyMapping::TotalKeys> m_keys;
};

}  // namespace zoper

#endif
