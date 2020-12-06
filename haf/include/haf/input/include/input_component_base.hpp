#ifndef HAF_INPUT_COMPONENT_BASE_INCLUDE_HPP
#define HAF_INPUT_COMPONENT_BASE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/scene/include/icomponent.hpp>
#include <haf/input/include/key.hpp>

namespace haf::input
{
class InputComponentBase : public scene::IComponent
{
public:
    bool isPressed(const Key key);

    static inline bool isAscii(const Key key) noexcept
    {
        return key >= Key::A && key <= Key::Z;
    }

    virtual char toAscii(const Key key) const noexcept;
    virtual bool isShiftPressed() const noexcept;
};
}  // namespace haf::input

#endif
