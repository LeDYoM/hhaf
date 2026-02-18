module;

#include "system/get_system.hpp"

export module haf:input:input_component;

import :events;
import :input_component_base;
import :input_system;
import :key;
import :core;

namespace haf::input
{
class InputComponent : public InputComponentBase
{
public:
    InputComponent()           = default;
    ~InputComponent() override = default;

    void update() override
    {
        if (attachedNode())
        {
            const sys::InputSystem& input_system{
                sys::getSystem<sys::InputSystem>(attachedNode())};

            for (const auto& pressedKey : input_system.pressedKeys())
            {
                KeyPressed(pressedKey);
            }

            for (const auto& releasedKey : input_system.releasedKeys())
            {
                KeyReleased(releasedKey);
            }
        }
    }

    evt::emitter<const Key&> KeyPressed;
    evt::emitter<const Key&> KeyReleased;
};
}  // namespace haf::input

#endif
