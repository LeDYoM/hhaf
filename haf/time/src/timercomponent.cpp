#include <haf/time/include/timercomponent.hpp>

#include <mtypes/include/function.hpp>
#include <mtypes/include/algoutils.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/scene/include/scenenode.hpp>

using namespace mtps;

namespace haf::time
{
TimerConnectorSPtr TimerComponent::addTimer(TimerType timerType,
                                            TimePoint timeOut,
                                            timer_callback_t callback)
{
    auto timerConnector(
        msptr<TimerConnector>(attachedNode()->dataWrapper<Timer>(), timerType,
                              std::move(timeOut), std::move(callback)));
    activeTimers_.emplace_back(timerConnector);
    return timerConnector;
}

void TimerComponent::update()
{
    activeTimers_.performUpdate([&](auto& timerConnector) {
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
}  // namespace haf::time
