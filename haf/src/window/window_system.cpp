#include "window.hpp"
#include "window_system.hpp"
#include <backend_dev/include/iwindow.hpp>
#include <backend/include/backend_factory.hpp>

#include "input/input_system.hpp"
#include "render/render_target.hpp"
#include "time/time_system.hpp"
#include "system/system_provider.hpp"
#include "utils/compile_time_constants.hpp"
#include "system/get_system.hpp"

#include <haf/include/time/time_point.hpp>
#include <haf/include/input/inputdriver_wrapper.hpp>

#include "window_log.hpp"

using namespace htps;
using namespace haf::time;

namespace haf::sys
{
WindowSystem::WindowSystem(sys::SystemProvider& system_provider) :
    SystemBase{system_provider}
{}

WindowSystem::~WindowSystem()
{
    auto* p_backend_window{systemProvider().backendFactory().getWindow()};
    if (p_backend_window != nullptr)
    {
        if (p_backend_window->isAlreadyCreated())
        {
            p_backend_window->closeWindow();
        }
    }
    WindowLogDisplayer::info_if(p_backend_window != nullptr, "Window closed");
}

bool WindowSystem::initialize(str const& window_config_file)
{
    m_window_configuration.loadConfiguration(subSystemViewer(),
                                             window_config_file);

    WindowLogDisplayer::info("Creating window...");

    // Create window object
    auto* p_backend_window{systemProvider().backendFactory().getWindow()};
    if (p_backend_window != nullptr)
    {
        backend::IWindow& backend_window{*p_backend_window};

        WindowLogDisplayer::info_if(backend_window.isAlreadyCreated(),
                                    "Window was already created.");

        // Create physical window if not already done
        if (!backend_window.isAlreadyCreated())
        {
            auto const& config{m_window_configuration};
            if (backend_window.createWindow(config.configuredWindowWidth(),
                                            config.configuredWindowHeight(),
                                            config.configuredBitsPerRed(),
                                            config.configuredBitsPerGreen(),
                                            config.configuredBitsPerBlue(),
                                            config.configuredBitsPerAlpha(), 0U,
                                            nullptr))
            {
                WindowLogDisplayer::info("Window creation completed");
            }
            else
            {
                WindowLogDisplayer::error(
                    "Cannot create window with the set properties");
            }
        }

        WindowLogDisplayer::debug("Window driver info: ",
                                  backend_window.info());
        WindowLogDisplayer::debug("Window settings: ",
                                  backend_window.settingsInfo());

        // If window created successfully, extract the render target
        // associated with the window.
        auto render_target{msptr<RenderTarget>(backend_window.renderTarget())};

        WindowLogDisplayer::debug("Extracted render target");

        // Also take the input driver.
        auto input_driver_wrapper{
            msptr<input::InputDriverWrapper>(p_backend_window->inputDriver())};

        WindowLogDisplayer::debug("Extracted input driver");

        m_window =
            msptr<Window>(p_backend_window, htps::move(input_driver_wrapper),
                          htps::move(render_target));

        return m_window != nullptr && m_window->renderTarget() != nullptr &&
            m_window->inputDriverWrapper() != nullptr;
    }
    else
    {
        WindowLogDisplayer::error("Backend window is nullptr!");
        return false;
    }
}

bool WindowSystem::preLoop()
{
    return m_window->preLoop(
        getSystem<sys::TimeSystem>(systemAccessPtr()).nowFrame());
}

void WindowSystem::postLoop()
{
    m_window->postLoop();
}

sptr<Window> const& WindowSystem::window() const
{
    return m_window;
}

}  // namespace haf::sys
