#include <host/include/host.hpp>
#include "host_private.hpp"

using namespace htps;

namespace haf::host
{
Host::HostPrivate::HostPrivate(const int argc, char const* const argv[]) :
    argc_{argc},
    argv_{argv},
    config_{argc, argv},
    params_{parpar::create(argc, argv)}
{}

HostedApplication& Host::HostPrivate::currentHostedApplication()
{
    return app_[index_current_app];
}

HostedApplication const& Host::HostPrivate::currentHostedApplication() const
{
    return app_[index_current_app];
}

rptr<IApp> Host::HostPrivate::currentApp()
{
    return currentHostedApplication().managed_app_.app;
}

str Host::HostPrivate::configuredFirstApp() const
{
    return config_.configuredFirstApp();
}

rptr<IApp const> Host::HostPrivate::currentApp() const
{
    return app_[index_current_app].managed_app_.app;
}

rptr<haf::sys::ISystemController> Host::HostPrivate::systemController() noexcept
{
    return system_loader_.systemController();
}

rptr<haf::sys::ISystemController const> Host::HostPrivate::systemController()
    const noexcept
{
    return system_loader_.systemController();
}

AppState Host::HostPrivate::currentAppState() noexcept
{
    return currentHostedApplication().app_state;
}

void Host::HostPrivate::setCurrentAppState(AppState const app_state) noexcept
{
    currentHostedApplication().app_state = app_state;
}

bool Host::HostPrivate::loopStep()
{
    return systemController()->runStep();
}

bool Host::HostPrivate::update()
{
    switch (currentAppState())
    {
        case AppState::NotInitialized:
            break;
        case AppState::ReadyToStart:
        {
            DisplayLog::info("Starting initialization of new App...");
            setCurrentAppState(AppState::Executing);
            system_loader_.loadFunctions();
            system_loader_.create();
            systemController()->init(currentApp(), argc_, argv_);

            DisplayLog::info(appDisplayNameAndVersion(*currentApp()),
                             ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep())
            {
                setCurrentAppState(AppState::ReadyToTerminate);
                DisplayLog::info(appDisplayNameAndVersion(*currentApp()), ": ",
                                 " is now ready to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            DisplayLog::info(appDisplayNameAndVersion(*currentApp()),
                             ": started termination");
            setCurrentAppState(AppState::Terminated);
            systemController()->terminate();
            system_loader_.destroy();
            return true;
            break;
        case AppState::Terminated:
            return true;
            break;
        default:
            break;
    }
    return false;
}

bool Host::HostPrivate::addApplication(ManagedApp managed_app, htps::str name)
{
    LogAsserter::log_assert(managed_app.app != nullptr,
                            "Received nullptr Application");

    // Search for a pointer to the same app
    auto const found = app_.cfind(HostedApplication{ManagedApp{}, name});

    // Store if the app is already registered
    bool const is_new_app{found == app_.cend()};

    DisplayLog::error_if(!is_new_app, "Application already registered");

    if (is_new_app)
    {
        DisplayLog::info("Starting Registering app...");
        app_.emplace_back(std::move(managed_app), std::move(name));
        DisplayLog::verbose("Starting new app...");
        setCurrentAppState(AppState::ReadyToStart);
    }

    return is_new_app;
}

}  // namespace haf::host
