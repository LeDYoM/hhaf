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
    priv_->window_configuration_.loadConfiguration(subSystemViewer(),
                                                   window_config_file);

    DisplayLog::info("Going to create Window");

    LogAsserter::log_assert(!priv_->backend_window_,
                            "Pointer to window already initialized");

    DisplayLog::info("Creating window...");

    // Create window object
    priv_->backend_window_ = systemProvider().backendFactory().getWindow();
    if (priv_->backend_window_ != nullptr)
    {
        backend::IWindow& backend_window(*priv_->backend_window_);

        DisplayLog::info_if(backend_window.isAlreadyCreated(),
                            "Window was already created.");

        // Create physical window if not already done
        if (!backend_window.isAlreadyCreated())
        {
            auto const& config{priv_->window_configuration_};
            if (backend_window.createWindow(config.configuredWindowWidth(),
                                            config.configuredWindowHeight(),
                                            config.configuredBitsPerRed(),
                                            config.configuredBitsPerGreen(),
                                            config.configuredBitsPerBlue(),
                                            config.configuredBitsPerAlpha(), 0U,
                                            nullptr))
            {
                DisplayLog::info("Window creation completed");
            }
            else
            {
                DisplayLog::error(
                    "Cannot create window with the set properties");
            }
        }

        DisplayLog::debug("Window driver info: ", backend_window.info());
        DisplayLog::debug("Window settings: ", backend_window.settingsInfo());

        // If window created successfully, extract the render target
        // associated with the window.
        priv_->render_target_ =
            msptr<RenderTarget>(backend_window.renderTarget());

        DisplayLog::debug("Extracted render target");

        // Also take the input driver.
        priv_->input_driver_wrapper_ = msptr<input::InputDriverWrapper>(
            priv_->backend_window_->inputDriver());

        DisplayLog::debug("Extracted input driver");

        return priv_->render_target_ != nullptr &&
            priv_->input_driver_wrapper_ != nullptr;
    }
    else
    {
        DisplayLog::error("Backend window is nullptr!");
        return false;
    }
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
