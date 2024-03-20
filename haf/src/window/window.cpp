#include "window.hpp"
#include <backend_dev/include/iwindow.hpp>

#include "input/input_system.hpp"
#include "input/input_driver_wrapper.hpp"
#include "render/render_target.hpp"
#include "time/time_system.hpp"
#include "utils/compile_time_constants.hpp"

#include <haf/include/time/time_point.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf::time;

namespace haf::sys
{
Window::Window(rptr<backend::IWindow> backend_window,
               sptr<input::InputDriverWrapper> input_driver_wrapper) :
    fps_counter{},
    m_backend_window{backend_window},
    m_input_driver_wrapper{htps::move(input_driver_wrapper)}
{}

Window::~Window() = default;

sptr<input::InputDriverWrapper> Window::inputDriverWrapper()
{
    return m_input_driver_wrapper;
}

sptr<input::InputDriverWrapper const> Window::inputDriverWrapper() const
{
    return m_input_driver_wrapper;
}

bool Window::preLoop(time::TimePoint const& time_since_start)
{
    if constexpr (ctc::ShowFPS)
    {
        fps_counter.updateFPS(time_since_start, m_backend_window, m_title);
    }

    return m_backend_window->processEvents(m_window_messages_receiver);
}

void Window::postLoop()
{
    m_backend_window->display();
}

}  // namespace haf::sys
