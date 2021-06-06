#ifndef ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP
#define ZOPER_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP

#include <haf/include/input/virtual_input_component.hpp>
#include <htypes/include/connection.hpp>

namespace haf::scene
{

class MenuPageInputComponent : public input::VirtualInputComponent
{
public:
    using BaseClass = input::VirtualInputComponent;
    using BaseClass::BaseClass;
    
    htps::emitter<> Up;
    htps::emitter<> Down;
    htps::emitter<> Left;
    htps::emitter<> Right;
    htps::emitter<> Selected;

private:
    void onKeyPressed(const input::Key&) override;

};
} // namespace zoper

#endif
