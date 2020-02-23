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
class TimerComponent : public scene::IComponent
{
public:
    TimerConnectorSPtr addTimer(TimerType timerType,
                                TimePoint timeOut, timer_callback_t callback);

    void update() override;
    void pause();
    void resume();
    void switchPause();

private:
    LockableVector<sptr<TimerConnector>> activeTimers_;
};
} // namespace lib::time

#endif
