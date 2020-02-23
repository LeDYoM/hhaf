#include "window.hpp"

#include <backend_dev/include/iwindow.hpp>
#include <backend/include/backendfactory.hpp>
#include <lib/include/liblog.hpp>
#include <lib/time/include/timepoint.hpp>
#include <lib/input/i_include/inputsystem.hpp>
#include <lib/render/include/rendertarget.hpp>
#include <lib/time/i_include/timesystem.hpp>
#include <lib/system/systemprovider.hpp>
#include <lib/input/include/inputdriver.hpp>

using namespace lib::time;

namespace lib::sys
{
struct Window::WindowPrivate final
{
    TimePoint lastTimeFps{0U};
    s32 lastFps{0};
    s32 currentFps{0};
    backend::IWindow *m_backendWindow{nullptr};
    sptr<input::InputDriver> input_driver_{nullptr};
    sptr<RenderTarget> m_renderTarget{nullptr};
    str title_{};
};

Window::Window(sys::SystemProvider &system_provider)
    : HostedAppService{system_provider},
      priv_{muptr<WindowPrivate>()}
{
    create();
}

Window::~Window() = default;

sptr<RenderTarget> Window::renderTarget()
{
    return priv_->m_renderTarget;
}

const sptr<RenderTarget> Window::renderTarget() const
{
    return priv_->m_renderTarget;
}

sptr<input::InputDriver> Window::inputDriver()
{
    return priv_->input_driver_;
}

const sptr<input::InputDriver> Window::inputDriver() const
{
    return priv_->input_driver_;
}

void Window::create()
{
    DisplayLog::info("Going to create Window");
    //        DisplayLog::info("Resolution:", wcp.width, "x", wcp.height ,"x", wcp.bpp);
    //        DisplayLog::info("Fullscreen:" , wcp.fullScreen);
    //        DisplayLog::info("Antialiasing:", wcp.antialiasing);

    log_assert(!priv_->m_backendWindow, "Cannot create window twice");
    DisplayLog::info("Creating window...");

    // Create window object
    priv_->m_backendWindow = systemProvider().backendFactory().getOrCreateWindow();
    DisplayLog::info("Window created");
    DisplayLog::info("Registering for view changes...");
    backend::IWindow &bw(*priv_->m_backendWindow);

    // Create physical window
    if (bw.createWindow(1024U, 768U, 32U))
    {
        DisplayLog::info("Hardware window created...");
        // If window created successfully, extract the render target
        // associated with the window.
        priv_->m_renderTarget = msptr<RenderTarget>(
            priv_->m_backendWindow->renderTarget());

        // Also take the input driver.
        priv_->input_driver_ = msptr<input::InputDriver>(
            priv_->m_backendWindow->inputDriver());
    }
    DisplayLog::info("Window creation completed");
}

bool Window::preLoop()
{
    backend::IWindow &bw(*priv_->m_backendWindow);
    const TimePoint eMs = systemProvider().timeSystem().timeSinceStart();
    if ((eMs - priv_->lastTimeFps).milliseconds() > 1000U)
    {
        priv_->lastTimeFps = eMs;
        priv_->lastFps = priv_->currentFps;
        priv_->currentFps = 0U;
        bw.setWindowTitle(make_str(priv_->title_, " FPS:", priv_->lastFps));
    }
    ++(priv_->currentFps);
    priv_->m_renderTarget->clear();

    return bw.processEvents();
}

void Window::postLoop()
{
    priv_->m_backendWindow->display();
}

void Window::onCreate()
{
    DisplayLog::info("Window created");
}

void Window::onDestroy()
{
    DisplayLog::info("Going to close Window");
    priv_->m_backendWindow->closeWindow();
    DisplayLog::info("Window closed");
}
} // namespace lib::sys
