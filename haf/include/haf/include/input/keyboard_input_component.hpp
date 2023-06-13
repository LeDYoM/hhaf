HAF_PRAGMA_ONCE
#ifndef HAF_COMPONENT_INPUT_KEYBOARD_INPUT_COMPONENT_INCLUDE_HPP
#define HAF_COMPONENT_INPUT_KEYBOARD_INPUT_COMPONENT_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/events/emitter.hpp>
#include <haf/include/input/key.hpp>
#include <haf/include/component/component_declaration.hpp>

namespace haf::input
{
class HAF_API KeyboardInputComponent
    : public component::ComponentBootStrap<KeyboardInputComponent>
{
public:
    static constexpr const core::str_view StaticTypeName{
        "KeyboardInputComponent"};

    void onAttached() override;

    evt::emitter<const Key&> KeyPressed;
    evt::emitter<const Key&> KeyReleased;

private:
    void update();
};
}  // namespace haf::input

#endif
