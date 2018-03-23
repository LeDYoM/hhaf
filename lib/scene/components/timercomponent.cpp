#include "timercomponent.hpp"
#include <mtypes/include/log.hpp>
#include <lib/scene/scene.hpp>

namespace lib::scene
{
    void TimerComponent::update()
    {
        using namespace time;
        if (!(m_activeTimers.empty())) {
            Clock clock;
            TimePoint t(clock.now());
            for (auto &uptr_timer : m_activeTimers) {
                // Get the shared pointer
                sptr<ITimer> sptr_timer(uptr_timer.lock());
                // If the pointer exists, use it
                if (sptr_timer) {
                    ITimer &timer(*sptr_timer);
                    if (timer.lastCheck - t > timer.delta) {
                        // Delta time has passed, so trigger
                        // the callback and update the timer
                        timer.callback(t);
                        timer.lastCheck = t;
                    }
                }
            }
        }
    }
}
