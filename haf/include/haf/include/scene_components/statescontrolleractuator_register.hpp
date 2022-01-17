#ifndef HAF_STATES_CONTROLLER_ACTUATOR_REGISTER_INCLUDE_HPP
#define HAF_STATES_CONTROLLER_ACTUATOR_REGISTERINCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene_components/statescontrolleractuator.hpp>

namespace haf::scene
{
template <typename T>
class StatesControllerActuatorRegister
{
public:
    void registerStatesControllerActuator(
        StatesControllerComponent<T>& statesController,
        StatesControllerActuator<T>& statesControllerActuator)
    {
        statesController.StateStarted.connect(
            [&statesControllerActuator](const T& startedState) {
                statesControllerActuator.onEnterState(startedState);
            });
        statesController.StateFinished.connect(
            [&statesControllerActuator](const T& startedState) {
                statesControllerActuator.onExitState(startedState);
            });
    }
};
}  // namespace haf::scene

#endif
