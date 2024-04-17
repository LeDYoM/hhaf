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
    logger::DisplayLog::info_if(p_backend_window != nullptr, StaticTypeName,
                                ": Window closed");
}

bool WindowSystem::initialize(str const& window_config_file)
{
    m_window_configuration.loadConfiguration(subSystemViewer(),
                                             window_config_file);

    logger::DisplayLog::info(StaticTypeName, ": Creating window...");

    // Create window object
    auto* p_backend_window{systemProvider().backendFactory().getWindow()};
    if (p_backend_window != nullptr)
    {
        backend::IWindow& backend_window{*p_backend_window};

        logger::DisplayLog::info_if(backend_window.isAlreadyCreated(),
                                    StaticTypeName,
                                    ": Window was already created.");

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
                logger::DisplayLog::info(StaticTypeName,
                                         ": Window creation completed");
            }
            else
            {
                logger::DisplayLog::error(
                    StaticTypeName,
                    ": Cannot create window with the set properties");
            }
        }

        logger::DisplayLog::debug(StaticTypeName, ": Window settings: ",
                                  backend_window.settingsInfo());

        logger::DisplayLog::debug(StaticTypeName, ": Extracted render target");

        m_window = msptr<Window>(p_backend_window);

        return m_window != nullptr;
    }
    else
    {
        logger::DisplayLog::error(StaticTypeName,
                                  ": Backend window is nullptr!");
        return false;
    }
}

void WindowSystem::preUpdate()
{
    m_window->preLoop(getSystem<sys::TimeSystem>(systemAccessPtr()).nowFrame());
}

void WindowSystem::update()
{
    m_window->loop();
}

void WindowSystem::postUpdate()
{
    m_window->postLoop();
}

sptr<Window> const& WindowSystem::window() const
{
    return m_window;
}

bool WindowSystem::exitRequested() const noexcept
{
    return m_window->windowWantsToExit();
}

}  // namespace haf::sys
