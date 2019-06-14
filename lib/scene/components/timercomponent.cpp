#include "timercomponent.hpp"

#include <mtypes/include/function.hpp>

#include <lib/include/liblog.hpp>
#include <lib/scene/scene.hpp>

namespace lib::scene
{
    void update_(vector_shared_pointers<TimerConnector> &activeTimers,
        function<void(sptr<TimerConnector>)> updateFunction)
    {
        if (!(activeTimers.empty())) 
        {
            for (auto &sptr_timerConnector : activeTimers) 
            {
                updateFunction(sptr_timerConnector);
            }
        }
    }

    void TimerComponent::update()
    {
        if (!(m_activeTimers.empty()))
        {
            bool someDeleted{ false };
            for (auto &timerConnector : m_activeTimers)
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
                        timerConnector.reset();
                        someDeleted = true;
                    }
                }
            }

            if (someDeleted) 
            {
                m_activeTimers.remove_values(nullptr);
            }
        }
    }

    void TimerComponent::pause()
    {
        m_activeTimers.for_each([](const sptr<TimerConnector>&timerConnector)
        {
            timerConnector->timer_->pause();
        });
    }

    void TimerComponent::resume()
    {
        m_activeTimers.for_each([](const sptr<TimerConnector>&timerConnector)
        {
            timerConnector->timer_->resume();
        });
    }

    void TimerComponent::switchPause()
    {
        m_activeTimers.for_each([](const sptr<TimerConnector>&timerConnector)
        {
            timerConnector->timer_->switchPause();
        });
    }
}
