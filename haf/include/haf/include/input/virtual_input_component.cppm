module;

#include "system/get_system.hpp"

export module haf:input:virtual_input_component;

import :input_system;
import :key;
import :input_component_base;
import :core;

namespace haf::input
{
class VirtualInputComponent : public InputComponentBase
{
public:
    VirtualInputComponent()           = default;
    ~VirtualInputComponent() override = default;

    void update() override
    {
        if (attachedNode() != nullptr)
        {
            sys::InputSystem const& input_system{
                sys::getSystem<sys::InputSystem>(attachedNode())};

            for (auto const pressedKey : input_system.pressedKeys())
            {
                onKeyPressed(pressedKey);
            }

            for (auto const releasedKey : input_system.releasedKeys())
            {
                onKeyReleased(releasedKey);
            }
        }
    }

private:
    virtual void onKeyPressed(Key const&) {}
    virtual void onKeyReleased(Key const&) {}
};
}  // namespace haf::input
