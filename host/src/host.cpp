#include <htypes/include/str.hpp>
#include <host/include/host.hpp>
#include <host/include/host_version.hpp>
#include <host/include/systemcontroller_loader.hpp>
#include "host_private.hpp"
#include <exception>
#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>
#include <haf/include/haf/system/include/isystemcontroller.hpp>

using namespace htps;

namespace haf::host
{
Host::Host(int argc, char* argv[]) : p_{muptr<HostPrivate>(argc, argv)}
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

    while (!p_->app_.empty())
    {
        HostedApplication& last = p_->app_.back();
        unloadApplication(last.app_name_);
    }
    DisplayLog::info("All applications unloaded");
}

bool Host::loadApplication(htps::str const& app_name)
{
    ManagedApp managed_app = p_->app_loader.loadApp(app_name);
    return p_->addApplication(managed_app.app, std::move(managed_app),
                              app_name);
}

bool Host::unloadApplication(htps::str const& app_name)
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

int Host::run()
{
    try
    {
        while (!p_->exit)
        {
            p_->exit = p_->update();
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        DisplayLog::error(e.what());
    }
    return 1;
}

}  // namespace haf::host
