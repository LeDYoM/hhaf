HTPS_PRAGMA_ONCE
#ifndef HAF_STATED_INPUT_COMPONENT_INCLUDE_HPP
#define HAF_STATED_INPUT_COMPONENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/input/stated_input_component_base.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>
#include <haf/include/events/connection.hpp>
#include <hlog/include/hlog.hpp>

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
