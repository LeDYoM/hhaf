#include "window.hpp"
#include "window_private.hpp"
#include <backend_dev/include/iwindow.hpp>
#include <backend/include/backendfactory.hpp>

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
Window::Window(sys::SystemProvider& system_provider) :
    SystemBase{system_provider}, priv_{muptr<WindowPrivate>()}
{}

Window::~Window() = default;

sptr<RenderTarget> Window::renderTarget()
{
    return priv_->render_target_;
}

sptr<RenderTarget const> Window::renderTarget() const
{
    return priv_->render_target_;
}

sptr<input::InputDriverWrapper> Window::inputDriverWrapper()
{
    return priv_->input_driver_wrapper_;
}

sptr<input::InputDriverWrapper const> Window::inputDriverWrapper() const
{
    return priv_->input_driver_wrapper_;
}

bool Window::initialize(str const& window_config_file)
{
    priv_->window_configuration_.loadConfiguration(
        subSystemViewer(), window_config_file);

    DisplayLog::info("Going to create Window");

    LogAsserter::log_assert(!priv_->backend_window_,
                            "Pointer to window already initialized");

    DisplayLog::info("Creating window...");

    // Create window object
    priv_->backend_window_ = systemProvider().backendFactory().getWindow();
    backend::IWindow& bw(*priv_->backend_window_);

    DisplayLog::info_if(bw.isAlreadyCreated(), "Window was already created.");

    // Create physical window if not already done
    if (!bw.isAlreadyCreated())
    {
        auto const& config{priv_->window_configuration_};
        if (bw.createWindow(config.configuredWindowWidth(),
                            config.configuredWindowHeight(),
                            config.configuredBitsPerRed(),
                            config.configuredBitsPerGreen(),
                            config.configuredBitsPerBlue(),
                            config.configuredBitsPerAlpha(), 0U, nullptr))
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
    priv_->render_target_ =
        msptr<RenderTarget>(priv_->backend_window_->renderTarget());

    // Also take the input driver.
    priv_->input_driver_wrapper_ =
        msptr<input::InputDriverWrapper>(priv_->backend_window_->inputDriver());
    DisplayLog::debug("Window driver info: ", bw.info());
    DisplayLog::debug("Window settings: ", bw.settingsInfo());
    return true;
}

bool Window::preLoop()
{
    if constexpr (ctc::ShowFPS)
    {
        priv_->updateFPS(
            systemProvider().system<TimeSystem>().timeSinceStart());
    }

    priv_->render_target_->clear();
    return priv_->backend_window_->processEvents();
}

void Window::postLoop()
{
    priv_->backend_window_->display();
}

}  // namespace haf::sys
