#include "window.hpp"

#include <backend_dev/include/iwindow.hpp>
#include <backend/include/backendfactory.hpp>
#include <lib/include/liblog.hpp>
#include <lib/time/include/timepoint.hpp>
#include <lib/input/i_include/inputsystem.hpp>
#include <lib/render/include/rendertarget.hpp>
#include <lib/time/i_include/timesystem.hpp>
#include <lib/system/i_include/systemprovider.hpp>
#include <lib/input/include/inputdriver.hpp>

using namespace lib::time;

namespace lib::sys
{
struct Window::WindowPrivate final
{
    TimePoint lastTimeFps{0U};
    mtps::s32 lastFps{0};
    mtps::s32 currentFps{0};
    mtps::rptr<backend::IWindow> m_backendWindow{nullptr};
    mtps::sptr<input::InputDriver> input_driver_{nullptr};
    mtps::sptr<RenderTarget> m_renderTarget{nullptr};
    mtps::str title_{};
};

Window::Window(sys::SystemProvider &system_provider)
    : AppService{system_provider},
      priv_{mtps::muptr<WindowPrivate>()}
{
}

Window::~Window() = default;

mtps::sptr<RenderTarget> Window::renderTarget()
{
    return priv_->m_renderTarget;
}

const mtps::sptr<RenderTarget> Window::renderTarget() const
{
    return priv_->m_renderTarget;
}

mtps::sptr<input::InputDriver> Window::inputDriver()
{
    return priv_->input_driver_;
}

const mtps::sptr<input::InputDriver> Window::inputDriver() const
{
    return priv_->input_driver_;
}

bool Window::create(mtps::uptr<win::WindowProperties> window_properties)
{
    if (window_properties == nullptr)
    {
        window_properties = mtps::muptr<win::WindowProperties>();
        window_properties->onAttached();
    }

    DisplayLog::info("Going to create Window");
    //        DisplayLog::info("Resolution:", wcp.width, "x", wcp.height ,"x", wcp.bpp);
    //        DisplayLog::info("Fullscreen:" , wcp.fullScreen);
    //        DisplayLog::info("Antialiasing:", wcp.antialiasing);

    log_assert(!priv_->m_backendWindow, "Cannot create window twice");
    DisplayLog::info("Creating window...");

    // Create window object
    priv_->m_backendWindow = systemProvider().backendFactory().getWindow();
    backend::IWindow &bw(*priv_->m_backendWindow);

    // Create physical window
    if (bw.createWindow(window_properties->width(), window_properties->height(),
        window_properties->bits_per_red(), window_properties->bits_per_green(),
        window_properties->bits_per_blue(), window_properties->bits_per_alpha(),
        0U, nullptr))
    {
        DisplayLog::info("Window created...");
        // If window created successfully, extract the render target
        // associated with the window.
        priv_->m_renderTarget = mtps::msptr<RenderTarget>(
            priv_->m_backendWindow->renderTarget());

        // Also take the input driver.
        priv_->input_driver_ = mtps::msptr<input::InputDriver>(
            priv_->m_backendWindow->inputDriver());
        DisplayLog::info("Window creation completed");
        return true;
    }
    else
    {
        DisplayLog::error("Cannot create window");
        return false;
    }
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
