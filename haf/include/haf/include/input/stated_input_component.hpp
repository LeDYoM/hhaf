#ifndef HAF_STATED_INPUT_COMPONENT_INCLUDE_HPP
#define HAF_STATED_INPUT_COMPONENT_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/input/stated_input_component_base.hpp>
#include <haf/include/component/component_container.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>
#include <hlog/include/hlog.hpp>

namespace haf::input
{
template <typename T>
class StatedInputComponent : public StatedInputComponentBase
{
    using BaseClass             = StatedInputComponentBase;
    using StatesController_t    = haf::scene::StatesControllerComponent<T>;
    using StatesControllerPtr_t = types::sptr<StatesController_t>;

public:
    void onKeyPressed(Key const& key) override
    {
        auto states_controller{
            attachedNode().components().componentOfType<StatesController_t>()};

        LogAsserter::log_assert(
            states_controller != nullptr,
            "StatedInputComponent requires a state component sibling");

        setCurrentState(
            static_cast<types::u32>(states_controller->currentState()));
        BaseClass::onKeyPressed(key);
    }

    void onKeyReleased(Key const&) override {}
};
}  // namespace haf::input

#endif
