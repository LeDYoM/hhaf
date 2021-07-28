#ifndef HAF_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP
#define HAF_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/lockablevector.hpp>
#include <haf/include/time/timerconnector.hpp>
#include <haf/include/time/timertype.hpp>
#include <haf/include/components/icomponent.hpp>

namespace haf::time
{
/**
 * @brief Component to manage a group of @b Timer elements
 * This class is a component that allows to create timers that can be latter
 * managed by the returned @b TimerConnectorSptr. They can be of different
 * @b TimerType.
 */
class TimerComponent : public component::IComponent
{
public:
    /**
     * @brief Create a Timer and get the connection to it.
     *
     * @param timerType Type of the timer created.
     * @param timeOut  Time for when the timer will trigger.
     * @param callback Function to be triggered.
     * @return TimerConnectorSPtr  htps::Objectto control the timer created.
     */
    TimerConnectorSPtr addTimer(TimerType timerType,
                                TimePoint timeOut,
                                timer_callback_t callback);

    void update() override;
    void pause();
    void resume();
    void switchPause();

private:
    htps::LockableVector<htps::sptr<TimerConnector>> activeTimers_;
};
}  // namespace haf::time

#endif
