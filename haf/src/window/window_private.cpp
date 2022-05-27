#include "window.hpp"
#include "window_private.hpp"
#include <backend_dev/include/iwindow.hpp>

using namespace htps;

namespace haf::sys
{
void Window::WindowPrivate::updateFPS(time::TimePoint const& time_point)
{
    fps_counter.updateFPS(time_point, m_backend_window, "");
}

}  // namespace haf::sys
