#include "window.hpp"

#include <backend_dev/include/iwindow.hpp>
#include <backend/include/backendfactory.hpp>

#include "input/inputsystem.hpp"
#include "render/rendertarget.hpp"
#include "time/timesystem.hpp"
#include "system/systemprovider.hpp"

#include <haf/include/time/timepoint.hpp>
#include <haf/include/input/inputdriver_wrapper.hpp>

#include <hlog/include/hlog.hpp>

using namespace htps;
using namespace haf::time;

namespace haf::sys
{
struct FPSCounter
{
    TimePoint lastTimeFps{0U};
    fast_u32 lastFps{0U};
    fast_u32 currentFps{0U};
};

struct Window::WindowPrivate final
{
    FPSCounter fps_counter;
    rptr<backend::IWindow> m_backendWindow{nullptr};
    sptr<input::InputDriverWrapper> input_driver_wrapper_;
    sptr<RenderTarget> m_renderTarget;
    str title_{};
};

Window::Window(sys::SystemProvider& system_provider) :
    SystemBase{system_provider}, priv_{muptr<WindowPrivate>()}
{}

Window::~Window() = default;

sptr<RenderTarget> Window::renderTarget()
{
    return priv_->m_renderTarget;
}

const sptr<RenderTarget> Window::renderTarget() const
{
    return priv_->m_renderTarget;
}

sptr<input::InputDriverWrapper> Window::inputDriverWrapper()
{
    return priv_->input_driver_wrapper_;
}

const sptr<input::InputDriverWrapper> Window::inputDriverWrapper() const
{
    return priv_->input_driver_wrapper_;
}

bool Window::create(uptr<win::WindowProperties> window_properties)
{
    if (window_properties == nullptr)
    {
        window_properties = muptr<win::WindowProperties>();
        window_properties->onAttached();
    }

    DisplayLog::info("Going to create Window");

    LogAsserter::log_assert(!priv_->m_backendWindow,
                            "Pointer to window already initialized");

    DisplayLog::info("Creating window...");

    // Create window object
    priv_->m_backendWindow = systemProvider().backendFactory().getWindow();
    backend::IWindow& bw(*priv_->m_backendWindow);

    DisplayLog::info_if(bw.isAlreadyCreated(), "Window was already created.");

    // Create physical window if not already done
    if (!bw.isAlreadyCreated())
    {
        if (bw.createWindow(window_properties->width(),
                            window_properties->height(),
                            window_properties->bits_per_red(),
                            window_properties->bits_per_green(),
                            window_properties->bits_per_blue(),
                            window_properties->bits_per_alpha(), 0U, nullptr))
        {
            DisplayLog::info("Window creation completed");
        }
        else
        {
            DisplayLog::error("Cannot create window");
            return false;
        }
    }

    // If window created successfully, extract the render target
    // associated with the window.
    priv_->m_renderTarget =
        msptr<RenderTarget>(priv_->m_backendWindow->renderTarget());

    // Also take the input driver.
    priv_->input_driver_wrapper_ =
        msptr<input::InputDriverWrapper>(priv_->m_backendWindow->inputDriver());
    DisplayLog::debug("Window driver info: ", bw.info());
    DisplayLog::debug("Window settings: ", bw.settingsInfo());
    return true;
}

bool Window::preLoop()
{
    backend::IWindow& bw(*priv_->m_backendWindow);
    auto& fps_counter{priv_->fps_counter};

    const TimePoint eMs{systemProvider().timeSystem().timeSinceStart()};

    if ((eMs - fps_counter.lastTimeFps).milliseconds() > 1000U)
    {
        fps_counter.lastTimeFps = eMs;
        fps_counter.lastFps     = fps_counter.currentFps;
        fps_counter.currentFps  = 0U;
        bw.setWindowTitle(
            make_str(priv_->title_, " FPS:", fps_counter.lastFps));
    }
    ++(fps_counter.currentFps);
    priv_->m_renderTarget->clear();

    return bw.processEvents();
}

void Window::postLoop()
{
    priv_->m_backendWindow->display();
}

}  // namespace haf::sys
