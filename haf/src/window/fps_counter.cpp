#include "fps_counter.hpp"
#include <backend_dev/include/iwindow.hpp>

using namespace htps;
using namespace haf::time;

namespace haf::sys
{
void FPSCounter::updateFPS(time::TimePoint const& time_since_start,
               htps::rptr<backend::IWindow> backend_window,
               htps::str const& base_title)
{
    static constexpr time::TimePoint OneSec{TimePoint_as_seconds(1U)};
    if (ellapsedUpdate(lastTimeFps, time_since_start, OneSec))
    {
        lastFps     = currentFps;
        currentFps  = 0U;
        m_lastWindowTitle = base_title;
        m_lastWindowTitle += " FPS: ";
        m_lastWindowTitle.append(lastFps);
        backend_window->setWindowTitle(m_lastWindowTitle);
    }
    ++(currentFps);
}

}  // namespace haf::sys
