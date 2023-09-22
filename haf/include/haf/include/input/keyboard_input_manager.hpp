HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_INPUT_KEYBOARD_INPUT_MANAGER_INCLUDE_HPP
#define HAF_COMPONENT_INPUT_KEYBOARD_INPUT_MANAGER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/events/emitter.hpp>
#include <haf/include/input/key.hpp>

namespace haf::sys
{
class ISystemProvider;
}

namespace haf::input
{
class KeyboardInputManager final
{
public:
    explicit KeyboardInputManager(
        sys::ISystemProvider& systemProvider) noexcept;
    evt::emitter<const Key&> KeyPressed;
    evt::emitter<const Key&> KeyReleased;
    void update();

private:
    sys::ISystemProvider& m_system_provider;
};
}  // namespace haf::input

#endif
