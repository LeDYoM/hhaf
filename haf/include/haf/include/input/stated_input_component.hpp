#ifndef HAF_STATED_INPUT_COMPONENT_INCLUDE_HPP
#define HAF_STATED_INPUT_COMPONENT_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/types/vector.hpp>
#include <haf/include/types/function.hpp>
#include <haf/include/input/virtual_input_component.hpp>
#include <haf/include/input/key.hpp>
#include <htypes/include/p_impl_pointer.hpp>

namespace haf::input
{
class StatedInputComponent : public VirtualInputComponent
{
    using BaseClass = VirtualInputComponent;

public:
    using InputInState = function<void()>;

    StatedInputComponent();
    ~StatedInputComponent() override;

    void onKeyPressed(Key const&) override;
    void onKeyReleased(Key const&) override;

    void addStateKeyInputFunction(types::u32 const value,
                                  InputInState key_pressed_function,
                                  InputInState key_released_function);

private:
    struct StatedInputComponentPrivate;
    htps::PImplPointer<StatedInputComponentPrivate> p_;
};
}  // namespace haf::input

#endif
