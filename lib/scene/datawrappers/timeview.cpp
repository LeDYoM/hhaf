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
        if (isPaused())
        {
            return time_paused_ - started_at_;
        }
        else
        {
            return now() - started_at_;
        }
    }

    void Timer::pause()
    {
        if (!isPaused())
        {
            is_paused_ = true;
            time_paused_ = now();
        }
    }

    void Timer::resume()
    {
        if (isPaused())
        {
            is_paused_ = false;
            started_at_ += (now() - time_paused_);
        }
    }

    void Timer::switchPause()
    {
        (void)(isPaused() ? resume() : pause());
    }

    void Timer::onCreated()
    {
        restart();
        is_paused_ = false;
        time_paused_ = TimePoint{}; 
    }
}
