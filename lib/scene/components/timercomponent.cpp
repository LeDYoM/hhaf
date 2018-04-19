#include "timercomponent.hpp"
#include <mtypes/include/log.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/scene.hpp>

namespace lib::scene
{
    void update_and_remove(vector<wptr<TimerConnector>> &activeTimers,
        function<void(sptr<TimerConnector>)> updateFunction)
    {
        if (!(activeTimers.empty())) {
            for (auto &wptr_timerConnector : activeTimers) {
                // Get the shared pointer
                sptr<TimerConnector> sptr_timerConnector(wptr_timerConnector.lock());
                // If the pointer exists, use it
                if (sptr_timerConnector) {
                    updateFunction(std::move(sptr_timerConnector));
                }
                else {
                    // The object does not exist anymore
                    wptr_timerConnector.reset();
                }
            }

            // Now, delete the elements
            activeTimers.remove_all_if([](const wptr<TimerConnector>& p) { return p.expired(); });
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

			update_and_remove(m_activeTimers, updateFunction);
            update_and_remove(m_oneShotTimers, updateFunction);
        }
    }
}
