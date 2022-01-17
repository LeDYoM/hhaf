#include <haf/include/time/timer_component.hpp>

#include <htypes/include/function.hpp>
#include <htypes/include/algoutils.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/time/timer.hpp>
#include <haf/include/time/time_view.hpp>
#include <haf/include/system/subsystem_view.hpp>

using namespace htps;

namespace haf::time
{
TimerConnectorSPtr TimerComponent::addTimer(TimerType timerType,
                                            TimePoint timeOut,
                                            timer_callback_t callback)
{
    auto timerConnector{msptr<TimerConnector>(
        muptr<Timer>(attachedNode()->subSystem<ITimeView>()), timerType,
        std::move(timeOut), std::move(callback))};
    activeTimers_.push_back(timerConnector);
    return timerConnector;
}

TimerConnectorSPtr TimerComponent::addFreeTimer()
{
    return addTimer(TimerType::Free, TimePoint{}, timer_callback_t{});
}

void TimerComponent::update()
{
    activeTimers_.performUpdate([this](auto& timerConnector) {
        // Perform update for each timer connector if and only if:
        // It has timed out and is not a free timer and is not paused
        if (timerConnector->timeOut() &&
            timerConnector->timer_type_ != TimerType::Free &&
            !timerConnector->isPaused())
        {
            // Delta time has passed, so trigger
            // the callback and update the timer
            timerConnector->emitter_(timerConnector->timer_->ellapsed());
            if (timerConnector->timer_type_ == TimerType::Continuous)
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
                 [](const sptr<TimerConnector>& timerConnector) {
                     timerConnector->timer_->pause();
                 });
}

void TimerComponent::resume()
{
    for_each_all(activeTimers_.current(),
                 [](const sptr<TimerConnector>& timerConnector) {
                     timerConnector->timer_->resume();
                 });
}

void TimerComponent::switchPause()
{
    for_each_all(activeTimers_.current(),
                 [](const sptr<TimerConnector>& timerConnector) {
                     timerConnector->timer_->switchPause();
                 });
}

void TimerComponent::removeTimer(TimerConnectorSPtr timer_to_remove)
{
    activeTimers_.erase_value(timer_to_remove);
}

}  // namespace haf::time
