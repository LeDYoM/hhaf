#pragma once

#ifndef LIB_VIRTUAL_INPUT_COMPONENT_INCLUDE_HPP
#define LIB_VIRTUAL_INPUT_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/input/include/input_component_base.hpp>
#include <lib/input/include/key.hpp>

namespace lib::input
{
class VirtualInputComponent : public InputComponentBase
{
public:
    VirtualInputComponent();
    ~VirtualInputComponent() override;

    void update() override;

private:
    virtual void onKeyPressed(const Key &key) {}
    virtual void onKeyReleased(const Key &key) {}
};
} // namespace lib::input

#endif
