#ifndef HAF_INPUT_COMPONENT_BASE_INCLUDE_HPP
#define HAF_INPUT_COMPONENT_BASE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene/icomponent.hpp>
#include <haf/include/input/key.hpp>

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
