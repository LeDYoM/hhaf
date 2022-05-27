#include "window.hpp"
#include "window_private.hpp"
#include <backend_dev/include/iwindow.hpp>
#include <backend/include/backend_factory.hpp>

#include "input/input_system.hpp"
#include "render/render_target.hpp"
#include "time/time_system.hpp"
#include "system/system_provider.hpp"
#include "utils/compile_time_constants.hpp"

#include <haf/include/time/time_point.hpp>
#include <haf/include/input/inputdriver_wrapper.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf::time;

namespace haf::sys
{
Window::Window(rptr<backend::IWindow> backend_window,
               sptr<input::InputDriverWrapper> input_driver_wrapper,
               sptr<RenderTarget> render_target) :
    priv_{muptr<WindowPrivate>(backend_window,
                               input_driver_wrapper,
                               render_target)}
{}

Window::~Window() = default;

sptr<RenderTarget> Window::renderTarget()
{
    return priv_->m_render_target;
}

sptr<RenderTarget const> Window::renderTarget() const
{
    return priv_->m_render_target;
}

sptr<input::InputDriverWrapper> Window::inputDriverWrapper()
{
    return priv_->m_input_driver_wrapper;
}

sptr<input::InputDriverWrapper const> Window::inputDriverWrapper() const
{
    return priv_->m_input_driver_wrapper;
}

void updateFPS(time::TimePoint const& time_point);

bool Window::preLoop()
{
    if constexpr (ctc::ShowFPS)
    {
//        priv_->updateFPS(
//            systemProvider().system<TimeSystem>().timeSinceStart());
    }

    priv_->m_render_target->clear();
    return priv_->m_backend_window->processEvents();
}

void Window::postLoop()
{
    priv_->m_backend_window->display();
}

}  // namespace haf::sys
