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
            const auto updateFunction([](sptr<TimerConnector> sptr_timer) {
                TimerConnector &timerConnector(*sptr_timer);
                if (timerConnector.timeOut()) {
                    // Delta time has passed, so trigger
                    // the callback and update the timer
                    timerConnector.m_emitter(timerConnector.m_timer.getElapsedTime());
                    timerConnector.m_timer.restart();
                }
            });

			update_(m_activeTimers, updateFunction);
            update_(m_oneShotTimers, updateFunction);
        }
    }
}
