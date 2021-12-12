#include "window.hpp"
#include "window_private.hpp"
#include <backend_dev/include/iwindow.hpp>

using namespace htps;

namespace haf::sys
{
void Window::WindowPrivate::updateFPS(time::TimePoint const& time_point)
{
    fps_counter.updateFPS(time_point, backend_window_, title_);
}

}  // namespace haf::sys
