#include <host/include/host.hpp>
#include <host/include/host_version.hpp>
#include <host/include/systemcontroller_loader.hpp>
#include "host_private.hpp"
#include <exception>
#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>
#include <haf/system/include/isystemcontroller.hpp>

using namespace mtps;

namespace haf::sys
{
Host::Host(int argc, char* argv[]) :
    p_{muptr<HostPrivate>(argc, argv)}, app_state_{AppState::NotInitialized}
{
    DisplayLog::info("Starting HostController...");
    DisplayLog::info("Host version: ", HostVersion, ".", HostSubversion, ".",
                     HostPatch, ".", HostTweak);
    DisplayLog::info("Parsing parameters...");
    p_->parseCommandLineParameters();
}

Host::~Host() = default;

bool Host::setApplication(rptr<IApp> iapp)
{
    LogAsserter::log_assert(iapp != nullptr, "Received nullptr Application");
    LogAsserter::log_assert(!p_->iapp_, "Application already set");

    if (!p_->iapp_ && iapp)
    {
        DisplayLog::info("Starting Registering app...");
        p_->iapp_ = iapp;
        DisplayLog::verbose("Starting new app...");
        app_state_ = AppState::ReadyToStart;
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
    switch (app_state_)
    {
        case AppState::NotInitialized:
            break;
        case AppState::ReadyToStart:
        {
            DisplayLog::info("Starting initialization of new App...");
            app_state_ = AppState::Executing;
            p_->system_loader_.loadFunctions();
            p_->system_loader_.create();
            p_->systemController()->init(p_->iapp_, p_->argc_, p_->argv_);

            DisplayLog::info(appDisplayNameAndVersion(*(p_->iapp_)),
                             ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep())
            {
                app_state_ = AppState::ReadyToTerminate;
                DisplayLog::info(appDisplayNameAndVersion(*(p_->iapp_)), ": ",
                                 " is now ready to terminate");
            }
            else if (app_state_ == AppState::ReadyToTerminate)
            {
                DisplayLog::info(appDisplayNameAndVersion(*(p_->iapp_)), ": ",
                                 " requested to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            DisplayLog::info(appDisplayNameAndVersion(*(p_->iapp_)),
                             ": started termination");
            app_state_ = AppState::Terminated;
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
        while (!exit)
        {
            if (update())
            {
                exit = true;
            }
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
        app_state_ == AppState::Executing,
        "Cannot terminate a program that is not in the executing state");
    app_state_ = AppState::ReadyToTerminate;
}
}  // namespace haf::sys
