HTPS_PRAGMA_ONCE
#ifndef HAF_INPUT_COMPONENT_BASE_INCLUDE_HPP
#define HAF_INPUT_COMPONENT_BASE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/component/component.hpp>
#include <haf/include/input/key.hpp>

namespace haf::input
{
class InputComponentBase : public component::Component
{
public:
    bool isPressed(const Key key);

    static inline bool isAscii(const Key key) noexcept
    {
        return key >= Key::A && key <= Key::Z;
    }

    virtual char toAscii(Key const key) const noexcept;
    virtual bool isShiftPressed() const noexcept;
};
}  // namespace haf::input

#endif
