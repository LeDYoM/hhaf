#include "timeview.hpp"

#include <lib/scene/scenenode.hpp>
#include <logger/include/log.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/system/timesystem.hpp>

namespace lib::scene
{
    TimeView::~TimeView() = default;

    TimePoint TimeView::now() const
    {
        return attachedNode()->parentScene()->sceneManager().systemProvider().timeSystem().now();
    }

    void Timer::restart()
    {
        started_at_ = attachedNode()->parentScene()->sceneManager().systemProvider().timeSystem().now();
    }

    TimePoint Timer::ellapsed() const
    {
        return now() - started_at_;
    }

    void Timer::onCreated()
    {
        restart();
    }    

    TimePoint PausableTimer::ellapsed() const
    {
        if (isPaused())
        {
            return time_paused_ - started_at_;
        }
        else
        {
            return Timer::ellapsed();
        }
    }

    void PausableTimer::pause()
    {
        if (!isPaused())
        {
            is_paused_ = true;
            time_paused_ = now();
        }
    }

    void PausableTimer::resume()
    {
        if (isPaused())
        {
            is_paused_ = false;
            started_at_ += (now() - time_paused_);
        }
    }

    void PausableTimer::switchPause()
    {
        (void)(isPaused() ? resume() : pause());
    }

    void PausableTimer::onCreated()
    {
        Timer::onCreated();
        is_paused_ = false;
        time_paused_ = TimePoint{}; 
    }    
}
