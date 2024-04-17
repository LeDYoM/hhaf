#include "window.hpp"
#include <backend_dev/include/iwindow.hpp>

#include "render/render_target.hpp"
#include "time/time_system.hpp"
#include "utils/compile_time_constants.hpp"

#include <haf/include/time/time_point.hpp>

#include <hlog/include/hlog.hpp>

using namespace haf::core;
using namespace haf::time;

namespace haf::sys
{
Window::Window(rptr<backend::IWindow> backend_window) :
    fps_counter{}, m_backend_window{backend_window}
{}

Window::~Window() = default;

sptr<input::KeyboardData> Window::sharedKeyboardData()
{
    return m_window_messages_receiver.sharedKeyboardData();
}

sptr<input::KeyboardData const> Window::sharedKeyboardData() const
{
    return m_window_messages_receiver.sharedKeyboardData();
}

void Window::preLoop(time::TimePoint const& time_since_start)
{
    if constexpr (ctc::ShowFPS)
    {
        fps_counter.updateFPS(time_since_start, m_backend_window, m_title);
    }
}

void Window::loop()
{
    m_backend_window->processEvents(m_window_messages_receiver);
}

void Window::postLoop()
{
    m_backend_window->display();
}

bool Window::windowWantsToExit() const noexcept
{
    return m_window_messages_receiver.exitRequested();
}

}  // namespace haf::sys
