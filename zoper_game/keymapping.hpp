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

    friend const mcs::Object& operator>>(const mcs::Object& obj,
                                          KeyMapping& key_mapping);
    friend mcs::Object& operator<<(mcs::Object& obj,
                                    const KeyMapping& key_mapping);

    bool serialize(mcs::Object&) const override;
    bool deserialize(mcs::Object const&) override;

private:
    htps::array<haf::input::Key, KeyMapping::TotalKeys> keys_;
};

}  // namespace zoper

#endif
