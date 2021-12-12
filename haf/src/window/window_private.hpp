#ifndef HAF_WINDOW_WINDOW_PRIVATE_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_PRIVATE_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include <haf/include/window/window_properties.hpp>
#include "fps_counter.hpp"
#include "window.hpp"

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

    void updateFPS(time::TimePoint const& time_point);
};
}  // namespace haf::sys

#endif
