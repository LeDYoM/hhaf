#ifndef ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP
#define ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP

#include <haf/input/include/virtual_input_component.hpp>
#include <htypes/include/connection.hpp>

namespace haf::scene
{

class MenuPageInputComponent : public input::VirtualInputComponent
{
public:
    using BaseClass = input::VirtualInputComponent;
    using BaseClass::BaseClass;
    
    mtps::emitter<> Up;
    mtps::emitter<> Down;
    mtps::emitter<> Left;
    mtps::emitter<> Right;
    mtps::emitter<> Selected;

private:
    void onKeyPressed(const input::Key&) override;

};
} // namespace zoper

#endif
