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

Host::Host(int argc, char* argv[]) : p_{make_pimplp<HostPrivate>(argc, argv)}
{
    logger::DisplayLog::info("Starting HostController...");
    logger::DisplayLog::info("Host version: ", host_VERSION, ".", host_SUBVERSION, ".",
                     host_PATCH, ".", host_TWEAK);
}

Host::~Host()
{
    logger::DisplayLog::info("Terminating Host...");
    logger::DisplayLog::verbose_if(!p_->app_group_.empty(), p_->app_group_.size(),
                           " pending apps to be terminated");

    [[maybe_unused]] auto const result{p_->unloadAllApplications()};

    logger::DisplayLog::info(result ? "All applications unloaded successfully"
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
        logger::DisplayLog::error(e.what());
    }
    catch (...)
    {
        logger::DisplayLog::error("Unknown object thrown");
    }
    return 1;
}

}  // namespace haf::host
