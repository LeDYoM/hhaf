export module haf:input:stated_input_component;

import :stated_imput_component_base;
import :component;
import :scene;
import :scene_components;
import :events;
import :core;

namespace haf::input
{
/**
 * @brief Component to control Input querties and dispatch them according to
 * the current state.
 * @tparam T A states enum
 */
template <typename T>
class StatedInputComponent : public StatedInputComponentBase
{
    using BaseClass = StatedInputComponentBase;

public:
    using InputInState          = BaseClass::InputInState;
    using StatesController_t    = haf::scene::StatesControllerComponent<T>;
    using StatesControllerPtr_t = htps::sptr<StatesController_t>;

    void addStateKeyInputFunction(T const& value,
                                  InputInState key_pressed_function,
                                  InputInState key_released_function)
    {
        BaseClass::addStateKeyInputFunction(static_cast<htps::u32>(value),
                                            htps::move(key_pressed_function),
                                            htps::move(key_released_function));
    }

    void onAttached()
    {
        BaseClass::onAttached();
        auto states_controller{
            attachedNode()->componentOfType<StatesController_t>()};

        LogAsserter::log_assert(
            states_controller != nullptr,
            "StatedInputComponent requires a state component sibling");

        states_controller->StateStarted.connect(
            [this](auto const state) { setProcessingState(state); });
    }

protected:
    void setProcessingState(T const& value)
    {
        BaseClass::setProcessingState(static_cast<htps::u32>(value));
    }
};
}  // namespace haf::input

#endif
