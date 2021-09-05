#include <haf/include/time/timercomponent.hpp>

#include <htypes/include/function.hpp>
#include <htypes/include/algoutils.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/system/datawrappercreator.hpp>

using namespace htps;

namespace haf::time
{
TimerConnectorSPtr TimerComponent::addTimer(TimerType timerType,
                                            TimePoint timeOut,
                                            timer_callback_t callback)
{
    auto timerConnector(msptr<TimerConnector>(
        attachedNode()->subsystems().dataWrapper<Timer>(), timerType,
        std::move(timeOut), std::move(callback)));
    activeTimers_.emplace_back(timerConnector);
    return timerConnector;
}

void TimerComponent::update()
{
    activeTimers_.performUpdate([this](auto& timerConnector) {
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
