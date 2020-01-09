#pragma once

#ifndef LIB_COMPONENT_INPUT_INCLUDE_HPP
#define LIB_COMPONENT_INPUT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/connection.hpp>
#include <lib/scene/components/input_component_base.hpp>
#include <lib/include/key.hpp>

namespace lib::scene
{
class InputComponent : public InputComponentBase
{
public:
    InputComponent();
    ~InputComponent() override;

    void update() override;

    emitter<const Key &> KeyPressed;
    emitter<const Key &> KeyReleased;
};
} // namespace lib::scene

#endif
