#include "timercomponent.hpp"

#include <mtypes/include/function.hpp>
#include <mtypes/include/algoutils.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/scene.hpp>

namespace lib::time
{
void TimerComponent::update()
{
    activeTimers_.performUpdate([&](auto& timerConnector)
    {
        if (timerConnector->timeOut())
        {
            // Delta time has passed, so trigger
            // the callback and update the timer
            timerConnector->m_emitter(timerConnector->timer_->ellapsed());
            if (timerConnector->m_timerType == TimerType::Continuous)
            {
                timerConnector->timer_->restart();
            }
            else
            {
                activeTimers_.erase_value(timerConnector);
            }
        }
    });
}

void TimerComponent::pause()
{
    for_each_all(activeTimers_.current(),
                 [](const sptr<TimerConnector> &timerConnector) {
                     timerConnector->timer_->pause();
                 });
}

void TimerComponent::resume()
{
    for_each_all(activeTimers_.current(),
                 [](const sptr<TimerConnector> &timerConnector) {
                     timerConnector->timer_->resume();
                 });
}

void TimerComponent::switchPause()
{
    for_each_all(activeTimers_.current(),
                 [](const sptr<TimerConnector> &timerConnector) {
                     timerConnector->timer_->switchPause();
                 });
}
} // namespace lib::time
