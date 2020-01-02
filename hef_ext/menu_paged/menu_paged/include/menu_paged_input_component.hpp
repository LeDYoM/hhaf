#pragma once

#ifndef ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP
#define ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <lib/scene/components/inputcomponent.hpp>

namespace lib::scene
{

class MenuPageInputComponent : public InputComponent
{
public:
    using BaseClass = InputComponent;
    ~MenuPageInputComponent() override = default;

    using InputComponent::InputComponent;
    void onAttached() override;

    emitter<> Up;
    emitter<> Down;
    emitter<> Left;
    emitter<> Right;
    emitter<> Selected;

private:
    ireceiver m_receiver;
};
} // namespace zoper

#endif
