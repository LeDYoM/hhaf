HTPS_PRAGMA_ONCE
#ifndef HAF_WINDOW_WINDOW_PRIVATE_INCLUDE_HPP
#define HAF_WINDOW_WINDOW_PRIVATE_INCLUDE_HPP

#include "haf_private.hpp"
#include <htypes/include/types.hpp>
#include "fps_counter.hpp"

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
    htps::rptr<backend::IWindow> m_backend_window{nullptr};
    htps::sptr<input::InputDriverWrapper> m_input_driver_wrapper;
    htps::sptr<RenderTarget> m_render_target;
    htps::str m_title;

    void updateFPS(time::TimePoint const& time_point);

    WindowPrivate(htps::rptr<backend::IWindow> backend_window,
                  htps::sptr<input::InputDriverWrapper> input_driver_wrapper,
                  htps::sptr<RenderTarget> render_target) :
        fps_counter{},
        m_backend_window{backend_window},
        m_input_driver_wrapper{input_driver_wrapper},
        m_render_target{render_target}
    {}
};
}  // namespace haf::sys

#endif
