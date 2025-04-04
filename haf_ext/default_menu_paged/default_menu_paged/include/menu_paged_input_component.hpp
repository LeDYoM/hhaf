#ifndef HAF_EXT_DEFAULT_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP
#define HAF_EXT_DEFAULT_MENU_MENUPAGE_INPUT_COMPONENT_INCLUDE_HPP

#include <haf/include/input/virtual_input_component.hpp>
#include <haf/include/events/connection.hpp>

namespace haf::exts::dmp
{
class MenuPageInputComponent : public input::VirtualInputComponent
{
public:
    using BaseClass = input::VirtualInputComponent;
    using BaseClass::BaseClass;

    evt::emitter<> Up;
    evt::emitter<> Down;
    evt::emitter<> Left;
    evt::emitter<> Right;
    evt::emitter<> Selected;

private:
    void onKeyPressed(const input::Key&) override;
};
}  // namespace haf::exts::dmp

#endif
