#include "host.hpp"

#include "host_private.hpp"
#include "systemcontroller_loader.hpp"
#include "host_version.hpp"  // In binary directory

#include <hosted_app/include/iapp.hpp>

#include <exception>

using namespace htps;

namespace haf::host
{
Host::Host(int argc, char* argv[]) : p_{muptr<HostPrivate>(argc, argv)}
{
    DisplayLog::info("Starting HostController...");
    DisplayLog::info("Host version: ", HostVersion, ".", HostSubversion, ".",
                     HostPatch, ".", HostTweak);
}

Host::~Host()
{
    DisplayLog::info("Terminating Host...");
    DisplayLog::verbose_if(!p_->app_group_.app_.empty(),
                           p_->app_group_.app_.size(),
                           " pending apps to be terminated");

    while (!p_->app_group_.app_.empty())
    {
        HostedApplication& last = p_->app_group_.app_.back();
        p_->unloadApplication(last.app_name_);
    }

    DisplayLog::info("All applications unloaded");
}

bool Host::initialize()
{
    return p_->initialize();
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
    catch (...)
    {
        DisplayLog::error("Unknown object thrown");
    }
    return 1;
}

}  // namespace haf::host
