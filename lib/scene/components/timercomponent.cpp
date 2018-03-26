#include "timercomponent.hpp"
#include <mtypes/include/log.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/scene.hpp>

namespace lib::scene
{
    void update_and_remove(vector<wptr<ITimer>> &activeTimers,
        function<void(sptr<ITimer>)> updateFunction)
    {
        using namespace time;
        if (!(activeTimers.empty())) {
            for (auto &wptr_timer : activeTimers) {
                // Get the shared pointer
                sptr<ITimer> sptr_timer(wptr_timer.lock());
                // If the pointer exists, use it
                if (sptr_timer) {
                    updateFunction(std::move(sptr_timer));
                }
                else {
                    // The object does not exist anymore
                    wptr_timer.reset();
                }
            }

            // Now, delete the elements
			activeTimers.remove_all_if([](const wptr<ITimer>& p) -> bool { return false; });
        }
    }

    void TimerComponent::update()
    {
        using namespace time;
        if (!(m_activeTimers.empty())) {
            Clock clock;
            TimePoint t(clock.now());
			update_and_remove(m_activeTimers, [t](sptr<ITimer> sptr_timer) {
				ITimer &timer(*sptr_timer);
				if (timer.lastCheck - t > timer.delta) {
					// Delta time has passed, so trigger
					// the callback and update the timer
					timer.callback(t);
					timer.lastCheck = t;
				}
			});
        }
    }
}
