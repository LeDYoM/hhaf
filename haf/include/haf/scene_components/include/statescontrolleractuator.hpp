#pragma once

#ifndef HAF_STATES_CONTROLLER_ACTUATOR_INCLUDE_HPP
#define HAF_STATES_CONTROLLER_ACTUATOR_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <haf/scene_components/include/statescontroller.hpp>

namespace haf
{
template <typename T>
class StatesControllerActuator
{
public:
    virtual void onEnterState(const T&) {}
    virtual void onExitState(const T&) {}
    virtual void onPushedState(const T&) {}
    virtual void onPoppedState(const T&) {}
    virtual void onPausedState(const T&) {}
    virtual void onResumedState(const T&) {}
};

template <typename T>
class StatesControllerActuatorRegister
{
public:
    void registerStatesControllerActuator(
        scene::StatesController<T>& statesController,
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
}  // namespace haf

#endif
