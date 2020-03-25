#pragma once

#ifndef LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP
#define LIB_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/lockablevector.hpp>
#include <lib/time/include/timerconnector.hpp>
#include <lib/time/include/timertype.hpp>
#include <lib/scene/include/icomponent.hpp>

namespace lib::time
{
/**
 * @brief Component to manage a group of @b Timer elements
 * This class is a component that allows to create timers that can be latter
 * managed by the returned @b TimerConnectorSptr. They can be of different
 * @b TimerType.
 */
class TimerComponent : public scene::IComponent
{
public:
    /**
     * @brief Create a Timer and get the connection to it.
     * 
     * @param timerType Type of the timer created.
     * @param timeOut  Time for when the timer will trigger.
     * @param callback Function to be triggered.
     * @return TimerConnectorSPtr  mtps::Objectto control the timer created.
     */
    TimerConnectorSPtr addTimer(TimerType timerType,
                                TimePoint timeOut, timer_callback_t callback);

    void update() override;
    void pause();
    void resume();
    void switchPause();

private:
   mtps::LockableVector<mtps::sptr<TimerConnector>> activeTimers_;
};
} // namespace lib::time

#endif
