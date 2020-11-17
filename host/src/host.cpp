#include <mtypes/include/str.hpp>
#include <host/include/host.hpp>
#include <host/include/host_version.hpp>
#include <host/include/systemcontroller_loader.hpp>
#include "host_private.hpp"
#include <exception>
#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>
#include <haf/include/haf/system/include/isystemcontroller.hpp>

using namespace mtps;

namespace haf::host
{
Host::Host(int argc, char* argv[]) :
    p_{muptr<HostPrivate>(argc, argv)}
{
    DisplayLog::info("Starting HostController...");
    DisplayLog::info("Host version: ", HostVersion, ".", HostSubversion, ".",
                     HostPatch, ".", HostTweak);
    DisplayLog::info("Parsing parameters...");
    p_->parseCommandLineParameters();
}

Host::~Host()
{
    DisplayLog::info("Terminating Host...");
    DisplayLog::verbose_if(!p_->app_.empty(), p_->app_.size(),
                           " pending apps to be terminated");

    while (p_->app_.empty())
    {
        HostedApplication& last = p_->app_.back();
        unloadApplication(last.app_name_);
    }
    DisplayLog::info("All applications unloaded");
}

bool Host::loadApplication(mtps::str const& app_name)
{
    ManagedApp managed_app = p_->app_loader.loadApp(app_name);
    return addApplication(managed_app.app, std::move(managed_app), app_name);
}

bool Host::addApplication(rptr<IApp> iapp,
                          ManagedApp managed_app,
                          mtps::str name)
{
    LogAsserter::log_assert(iapp != nullptr, "Received nullptr Application");

    // Search for a pointer to the same app
    auto const found = p_->app_.cfind(HostedApplication{name});

    // Store if the app is already registered
    bool const is_reapeated{found != p_->app_.cend()};

    if (!is_reapeated)
    {
        DisplayLog::info("Starting Registering app...");
        p_->app_.emplace_back(std::move(iapp), std::move(managed_app),
                              std::move(name));
        DisplayLog::verbose("Starting new app...");
        p_->app_state_ = AppState::ReadyToStart;
        return true;
    }
    else
    {
        DisplayLog::info("Application already registered");
        return false;
    }
}

bool Host::unloadApplication(mtps::str const& app_name)
{
    // First step, search the app in the array
    auto const app_iterator =
        p_->app_.find_if([&app_name](HostedApplication const& app) {
            return app.app_name_ == app_name;
        });

    if (app_iterator != p_->app_.end())
    {
        // Aplication found. Execute unload steps.
        p_->app_loader.unloadApp(app_iterator->managed_app_);

        auto const old_size = p_->app_.size();

        // Remove the application from the list
        p_->app_.erase_iterator(app_iterator, p_->app_.end());

        auto const new_size = p_->app_.size();

        // Show logs informing the user
        DisplayLog::info_if(old_size != new_size, "Application ", app_name,
                            " unloaded");

        DisplayLog::info_if(old_size == new_size, "Application ", app_name,
                            " unloaded, but cannot be deleted");

        return true;
    }

    return false;
}

str appDisplayNameAndVersion(const IApp& app)
{
    return make_str(app.getName(), "(", app.getVersion(), ".",
                    app.getSubVersion(), ".", app.getPatch(), ")");
}

bool Host::update()
{
    switch (p_->app_state_)
    {
        case AppState::NotInitialized:
            break;
        case AppState::ReadyToStart:
        {
            DisplayLog::info("Starting initialization of new App...");
            p_->app_state_ = AppState::Executing;
            p_->system_loader_.loadFunctions();
            p_->system_loader_.create();
            p_->systemController()->init(p_->currentApp(), p_->argc_,
                                         p_->argv_);

            DisplayLog::info(appDisplayNameAndVersion(*(p_->currentApp())),
                             ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep())
            {
                p_->app_state_ = AppState::ReadyToTerminate;
                DisplayLog::info(appDisplayNameAndVersion(*(p_->currentApp())),
                                 ": ", " is now ready to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            DisplayLog::info(appDisplayNameAndVersion(*(p_->currentApp())),
                             ": started termination");
            p_->app_state_ = AppState::Terminated;
            p_->systemController()->terminate();
            p_->system_loader_.destroy();
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

int Host::run()
{
    try
    {
        while (!p_->exit)
        {
            p_->exit = update();
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        DisplayLog::error(e.what());
    }
    return 1;
}

bool Host::loopStep()
{
    return p_->systemController()->runStep();
}

void Host::exitProgram()
{
    LogAsserter::log_assert(
        p_->app_state_ == AppState::Executing,
        "Cannot terminate a program that is not in the executing state");
    p_->app_state_ = AppState::ReadyToTerminate;
}
}  // namespace haf::host
