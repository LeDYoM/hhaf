#include "window.hpp"

#include <backend_dev/include/irendertarget.hpp>
#include <backend/include/backendfactory.hpp>
#include <lib/include/liblog.hpp>
#include <lib/include/core/timepoint.hpp>
#include <lib/system/inputsystem.hpp>
#include <lib/system/rendertarget.hpp>
#include <lib/system/timesystem.hpp>
#include <lib/system/systemprovider.hpp>

namespace lib::core
{
    struct Window::WindowPrivate final
    {
        TimePoint lastTimeFps{ 0U };
        s32 lastFps{ 0 };
        s32 currentFps{ 0 };
        backend::IWindow* m_backendWindow{nullptr};
        sptr<RenderTarget> m_renderTarget{nullptr};
        str title_{};
    };

    Window::Window(core::SystemProvider &system_provider)
        : HostedAppService{ system_provider },
        priv_{ muptr<WindowPrivate>() }
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

    backend::IInputDriver* Window::inputDriver()
    {
        return priv_->m_backendWindow->inputDriver();
    }

    const backend::IInputDriver* Window::inputDriver() const
    {
        return priv_->m_backendWindow->inputDriver();
    }

    void Window::create()
    {
        log_debug_info("Going to create Window");
//        log_debug_info("Resolution:", wcp.width, "x", wcp.height ,"x", wcp.bpp);
//        log_debug_info("Fullscreen:" , wcp.fullScreen);
//        log_debug_info("Antialiasing:", wcp.antialiasing);

        assert_release(!priv_->m_backendWindow, "Cannot create window twice");
        log_debug_info("Creating window...");

        // Create window object
        priv_->m_backendWindow = systemProvider().backendFactory().getOrCreateWindow();
        log_debug_info("Window created");
        log_debug_info("Registering for view changes...");
        backend::IWindow &bw(*priv_->m_backendWindow);

        // Create physical window
        if (bw.createWindow(1024U, 768U, 32U))
        {
            log_debug_info("Hardware window created...");
            // If window created successfully, extract the render target
            // associated with the window.
            priv_->m_renderTarget = msptr<RenderTarget>(
                    priv_->m_backendWindow->renderTarget());

            // Also extract the input driver
//            priv_->input_driver_ = sptr<backend::IInputDriver>(
//                priv_->m_backendWindow->inputDriver());
        }
        log_debug_info("Window creation completed");
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
        log_debug_info("Window created");
    }

    void Window::onDestroy()
    {
        log_debug_info("Going to close Window");
        priv_->m_backendWindow->closeWindow();
        log_debug_info("Window closed");
    }
}
