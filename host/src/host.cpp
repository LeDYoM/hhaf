#include "host.hpp"

#include "host_internal.hpp"
#include <hosted_app/include/iapp.hpp>

#include <exception>

using namespace htps;

namespace haf::host
{
struct Host::HostPrivate : public HostInternal
{
    using HostInternal::HostInternal;
};

Host::Host(int argc, char* argv[]) : p_{muptr<HostPrivate>(argc, argv)}
{
    DisplayLog::info("Starting HostController...");
    DisplayLog::info("Host version: ", host_VERSION, ".", host_SUBVERSION, ".",
                     host_PATCH, ".", host_TWEAK);
}

Host::~Host()
{
    DisplayLog::info("Terminating Host...");
    DisplayLog::verbose_if(!p_->app_group_.empty(), p_->app_group_.size(),
                           " pending apps to be terminated");

    [[maybe_unused]] auto const result{p_->unloadAllApplications()};

    DisplayLog::info(result ? "All applications unloaded successfully"
                            : "Problem unloading some applications");
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
