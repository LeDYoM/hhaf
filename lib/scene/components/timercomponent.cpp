#include "timercomponent.hpp"
#include <mtypes/include/log.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/scene.hpp>

namespace lib::scene
{
    void update_(vector_shared_pointers<TimerConnector> &activeTimers,
        function<void(sptr<TimerConnector>)> updateFunction)
    {
        if (!(activeTimers.empty())) {
            for (auto &sptr_timerConnector : activeTimers) {
                updateFunction(sptr_timerConnector);
            }
        }
    }

    void TimerComponent::update()
    {
        if (!(m_activeTimers.empty())) {
            decltype(m_activeTimers) activeTimerstoDelete(m_activeTimers.size());

            bool someDeleted{ false };
            for (auto &sptr_timerConnector : m_activeTimers) {
                TimerConnector &timerConnector{ *sptr_timerConnector };
                if (timerConnector.timeOut()) {
                    // Delta time has passed, so trigger
                    // the callback and update the timer
                    timerConnector.m_emitter(timerConnector.m_timer.getElapsedTime());
                    if (timerConnector.m_timerType == TimerType::Continuous) {
                        timerConnector.m_timer.restart();
                    } else {
                        sptr_timerConnector.reset();
                        someDeleted = true;
                    }
                }
            }

            if (someDeleted) {
                m_activeTimers.remove_values(nullptr);
            }
        }
    }

    void TimerComponent::pause()
    {
        m_activeTimers.for_each([](const sptr<TimerConnector>&timerConnector) {
            timerConnector->m_timer.pause();
        });
    }

    void TimerComponent::resume()
    {
        m_activeTimers.for_each([](const sptr<TimerConnector>&timerConnector) {
            timerConnector->m_timer.resume();
        });
    }

    void TimerComponent::switchPause()
    {
        m_activeTimers.for_each([](const sptr<TimerConnector>&timerConnector) {
            timerConnector->m_timer.switchPause();
        });
    }
}
