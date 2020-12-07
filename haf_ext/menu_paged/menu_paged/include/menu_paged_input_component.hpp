#ifndef ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP
#define ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/rect.hpp>
#include <haf/input/include/inputcomponent.hpp>

namespace haf::scene
{

class MenuPageInputComponent : public input::InputComponent
{
public:
    using input::InputComponent::InputComponent;
    using BaseClass = input::InputComponent;
    ~MenuPageInputComponent() override = default;
    void onAttached() override;

    mtps::emitter<> Up;
    mtps::emitter<> Down;
    mtps::emitter<> Left;
    mtps::emitter<> Right;
    mtps::emitter<> Selected;

};
} // namespace zoper

#endif
