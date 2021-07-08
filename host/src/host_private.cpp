#include "host_private.hpp"
#include "host.hpp"

using namespace htps;

namespace haf::host
{
Host::HostPrivate::HostPrivate(const int argc, char const* const argv[]) :
    argc_{argc},
    argv_{argv},
    backend_factory_{nullptr, nullptr},
    config_{argc, argv},
    params_{parpar::create(argc, argv)}
{}

HostedApplication& Host::HostPrivate::currentHostedApplication()
{
    return app_group_.currentHostedApplication();
}

HostedApplication const& Host::HostPrivate::currentHostedApplication() const
{
    return app_group_.currentHostedApplication();
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
    return currentHostedApplication().managed_app_.app;
}

rptr<sys::ISystemController> Host::HostPrivate::systemController() noexcept
{
    return system_loader_.systemController();
}

rptr<sys::ISystemController const> Host::HostPrivate::systemController()
    const noexcept
{
    return system_loader_.systemController();
}

AppState Host::HostPrivate::currentAppState() noexcept
{
    return currentHostedApplication().app_state;
}

bool Host::HostPrivate::initialize()
{
    backend_factory_ =
        uptr<backend::BackendFactory, void (*)(haf::backend::BackendFactory*)>(
            createBackendFactory(), destroyBackendFactory);

    return loadApplication(configuredFirstApp()) && backend_factory_ != nullptr;
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
            app_group_.setCurrentAppState(AppState::Executing);
            auto const result = system_loader_.loadFunctions();
            if (result != SystemControllerLoader::ResultType::Success)
            {
                DisplayLog::error("Cannot load haf system!");
                app_group_.setCurrentAppState(AppState::ReadyToTerminate);
            }
            else if (!system_loader_.create())
            {
                DisplayLog::error("Cannot create haf system!");
                app_group_.setCurrentAppState(AppState::ReadyToTerminate);
            }
            else
            {
                systemController()->init(currentApp(), backend_factory_.get(), argc_, argv_);

                DisplayLog::info(appDisplayNameAndVersion(*currentApp()),
                                 ": Starting execution...");
            }
        }
        break;
        case AppState::Executing:
        {
            if (loopStep())
            {
                app_group_.setCurrentAppState(AppState::ReadyToTerminate);
                DisplayLog::info(appDisplayNameAndVersion(*currentApp()), ": ",
                                 " is now ready to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            DisplayLog::info(appDisplayNameAndVersion(*currentApp()),
                             ": started termination");
            app_group_.setCurrentAppState(AppState::Terminated);
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
    return app_group_.try_add_app(std::move(managed_app), std::move(name));
}

bool Host::HostPrivate::loadApplication(htps::str const& app_name)
{
    ManagedApp managed_app = app_loader.loadApp(app_name);
    return managed_app.app != nullptr
        ? addApplication(std::move(managed_app), app_name)
        : false;
}

bool Host::HostPrivate::unloadApplication(htps::str const& app_name)
{
    if (app_group_.appExists(app_name))
    {
        // This is safe, given that app exists
        auto& app = app_group_.getAppByName(app_name)->managed_app_;
        app_loader.unloadApp(app);
        return app_group_.removeApp(app_name);
    }
    return false;
}

}  // namespace haf::host
