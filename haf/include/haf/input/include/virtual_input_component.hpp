#pragma once

#ifndef HAF_VIRTUAL_INPUT_COMPONENT_INCLUDE_HPP
#define HAF_VIRTUAL_INPUT_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/input/include/input_component_base.hpp>
#include <haf/input/include/key.hpp>

namespace haf::input
{
class VirtualInputComponent : public InputComponentBase
{
public:
    VirtualInputComponent();
    ~VirtualInputComponent() override;

    void update() override;

private:
    virtual void onKeyPressed(const Key &) {}
    virtual void onKeyReleased(const Key &) {}
};
} // namespace haf::input

#endif
