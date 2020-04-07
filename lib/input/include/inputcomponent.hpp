#pragma once

#ifndef HAF_COMPONENT_INPUT_INCLUDE_HPP
#define HAF_COMPONENT_INPUT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/input/include/input_component_base.hpp>
#include <lib/input/include/key.hpp>

namespace haf::input
{
class InputComponent : public InputComponentBase
{
public:
    InputComponent();
    ~InputComponent() override;

    void update() override;

    mtps::emitter<const Key &> KeyPressed;
    mtps::emitter<const Key &> KeyReleased;
};
} // namespace haf::input

#endif
