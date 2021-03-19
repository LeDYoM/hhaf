#ifndef HAF_HOST_PRIVATE_INCLUDE_HPP
#define HAF_HOST_PRIVATE_INCLUDE_HPP

#include "hosted_application.hpp"
#include <hosted_app/include/iapp.hpp>
#include <host/include/apploader.hpp>
#include "host_config.hpp"
#include <haf/system/include/isystemcontroller.hpp>
#include <hlog/include/hlog.hpp>
#include <agloader/include/loader.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/parpar.hpp>
#include <htypes/include/object.hpp>
#include <htypes/include/parpar.hpp>

#include <fstream>
#include <string>

using namespace htps;

namespace haf::host
{
enum class AppState : htps::u8
{
    NotInitialized,
    ReadyToStart,
    Executing,
    ReadyToTerminate,
    Terminated
};

class Host::HostPrivate final
{
public:
    HostPrivate(const int argc, char const* const argv[]) :
        argc_{argc},
        argv_{argv},
        config_{argc, argv},
        params_{parpar::create(argc, argv)},
        app_state_{AppState::NotInitialized}
    {}

    int const argc_;
    char const* const* const argv_;

    HostConfig config_;
    parpar::ParametersParser params_;
    SystemControllerLoader system_loader_;
    vector<HostedApplication> app_;
    u32 index_current_app{0U};
    AppLoader app_loader;
    rptr<IApp> currentApp() { return app_[index_current_app].iapp_; }

    str configuredFirstApp() const
    {
        return config_.configuredFirstApp();
    }

    rptr<IApp const> currentApp() const
    {
        return app_[index_current_app].iapp_;
    }

    inline rptr<ISystemController> systemController() noexcept
    {
        return system_loader_.systemController();
    }

    inline rptr<ISystemController const> systemController() const noexcept
    {
        return system_loader_.systemController();
    }

    AppState currentAppState() noexcept { return app_state_; }

    void setCurrentAppState(AppState const app_state) noexcept
    {
        app_state_ = app_state;
    }

    bool loopStep() { return systemController()->runStep(); }

    bool update()
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
                    DisplayLog::info(appDisplayNameAndVersion(*currentApp()),
                                     ": ", " is now ready to terminate");
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

    bool addApplication(rptr<IApp> iapp, ManagedApp managed_app, htps::str name)
    {
        LogAsserter::log_assert(iapp != nullptr,
                                "Received nullptr Application");

        // Search for a pointer to the same app
        auto const found = app_.cfind(HostedApplication{name});

        // Store if the app is already registered
        bool const is_new_app{found == app_.cend()};

        DisplayLog::error_if(!is_new_app, "Application already registered");

        if (is_new_app)
        {
            DisplayLog::info("Starting Registering app...");
            app_.emplace_back(std::move(iapp), std::move(managed_app),
                              std::move(name));
            DisplayLog::verbose("Starting new app...");
            app_state_ = AppState::ReadyToStart;
        }

        return is_new_app;
    }

    str simulation_input_file;
    str simulation_output_file;
    bool exit{false};
    AppState app_state_;
};

}  // namespace haf::host

#endif
