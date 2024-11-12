HTPS_PRAGMA_ONCE
#ifndef HAF_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP
#define HAF_COMPONENT_TIMER_COMPONENTEMENT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/lockable_vector.hpp>
#include <haf/include/time/timer_connector.hpp>
#include <haf/include/time/timer_type.hpp>
#include <haf/include/component/component.hpp>

namespace haf::time
{
/**
 * @brief Component to manage a group of @b Timer elements
 * This class is a component that allows to create timers that can be latter
 * managed by the returned @b TimerConnectorSptr. They can be of different
 * @b TimerType.
 */
class TimerComponent : public component::Component
{
public:
    /**
     * @brief Create a Timer and get the connection to it.
     *
     * @param timerType Type of the timer created.
     * @param timeOut  Time for when the timer will trigger.
     * @param callback Function to be triggered.
     * @return TimerConnectorSPtr  Object to control the timer created.
     */
    TimerConnectorSPtr addTimer(TimerType timerType,
                                TimePoint timeOut,
                                timer_callback_t callback);

    TimerConnectorSPtr addFreeTimer();

    void removeTimer(TimerConnectorSPtr timer_to_remove);

    void update() override;
    void pause();
    void resume();
    void switchPause();

private:
    htps::LockableVector<TimerConnectorSPtr> activeTimers_;
};
}  // namespace haf::time

#endif
