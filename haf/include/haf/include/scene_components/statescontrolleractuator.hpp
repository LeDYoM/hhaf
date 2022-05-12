HTPS_PRAGMA_ONCE
#ifndef HAF_STATES_CONTROLLER_ACTUATOR_INCLUDE_HPP
#define HAF_STATES_CONTROLLER_ACTUATOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/scene_components/states_controller_component.hpp>

namespace haf::scene
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

}  // namespace haf::scene

#endif
