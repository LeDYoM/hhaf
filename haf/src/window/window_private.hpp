HTPS_PRAGMA_ONCE
#ifndef HAF_WINDOW_WINDOW_PRIVATE_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_PRIVATE_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include "fps_counter.hpp"
#include "window_configuration.hpp"

namespace haf::backend
{
    class IWindow;
}

namespace haf::input
{
class InputDriverWrapper;
}

namespace haf::time
{
    class TimePoint;
}

namespace haf::sys
{
struct HAF_PRIVATE Window::WindowPrivate final
{
    FPSCounter fps_counter;
    htps::rptr<backend::IWindow> backend_window_{nullptr};
    htps::sptr<input::InputDriverWrapper> input_driver_wrapper_;
    htps::sptr<RenderTarget> render_target_;
    htps::str title_;
    WindowConfiguration window_configuration_;

    void updateFPS(time::TimePoint const& time_point);
};
}  // namespace haf::sys

#endif
