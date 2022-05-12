HTPS_PRAGMA_ONCE
#ifndef HAF_STATED_INPUT_COMPONENT_BASE_INCLUDE_HPP
#define HAF_STATED_INPUT_COMPONENT_BASE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <haf/include/input/virtual_input_component.hpp>
#include <haf/include/input/key.hpp>

namespace haf::input
{
class StatedInputComponentBase : public VirtualInputComponent
{
    using BaseClass = VirtualInputComponent;

public:
    using InputInState = htps::function<void(Key const&)>;

    StatedInputComponentBase();
    ~StatedInputComponentBase() override;

    void onKeyPressed(Key const&) override;
    void onKeyReleased(Key const&) override;

protected:
    void addStateKeyInputFunction(htps::u32 const value,
                                  InputInState key_pressed_function,
                                  InputInState key_released_function);

    void setProcessingState(htps::u32 const current_state);

private:
    struct StatedInputComponentBasePrivate;
    htps::PImplPointer<StatedInputComponentBasePrivate> p_;
};
}  // namespace haf::input

#endif
