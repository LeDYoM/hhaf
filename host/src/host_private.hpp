#pragma once

#ifndef HAF_HOST_PRIVATE_INCLUDE_HPP
#define HAF_HOST_PRIVATE_INCLUDE_HPP

#include <hosted_app/include/iapp.hpp>
#include <host/include/apploader.hpp>
#include <haf/system/include/isystemcontroller.hpp>
#include <hlog/include/hlog.hpp>
#include <loader/include/loader.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/parpar.hpp>
#include <mtypes/include/object.hpp>
#include <mtypes/include/parpar.hpp>

using namespace mtps;

namespace haf::host
{
enum class AppState : mtps::u8
{
    NotInitialized,
    ReadyToStart,
    Executing,
    ReadyToTerminate,
    Terminated
};

class HostedApplication final
{
public:
    HostedApplication(str app_name) noexcept : app_name_{std::move(app_name)} {}
    HostedApplication(rptr<IApp> iapp,
                      ManagedApp managed_app,
                      str app_name) noexcept :
        iapp_{iapp},
        managed_app_{std::move(managed_app)},
        app_name_{std::move(app_name)}
    {}

    rptr<IApp> iapp_{nullptr};
    ManagedApp managed_app_;
    str app_name_;
};

bool operator==(HostedApplication const& lhs,
                HostedApplication const& rhs) noexcept
{
    return lhs.app_name_ == rhs.app_name_;
}

class Host::HostPrivate final
{
public:
    HostPrivate(const int argc, char const* const argv[]) :
        argc_{argc},
        argv_{argv},
        params_{parpar::create(argc, argv)},
        // Hardcoded default configuration
        // TODO
        configuration_{{}},
        app_state_{AppState::NotInitialized}
    {}

    bool parseCommandLineParameters()
    {
        if (params_.hasParameters())
        {
            auto const simulation_input = params_.optionValue("simin");
            // If the parameter simin exists
            if (simulation_input.first)
            {
                simulation_input_file = simulation_input.second;
                DisplayLog::debug("Parameter simin found eith value: ",
                                  simulation_input_file);
            }
        }
        return true;
    }
    parpar::ParametersParser params_;

    Dictionary<str> configuration_;
    SystemControllerLoader system_loader_;
    vector<HostedApplication> app_;
    u32 index_current_app{0U};
    AppLoader app_loader;

    rptr<IApp> currentApp() { return app_[index_current_app].iapp_; }

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

    int const argc_;
    char const* const* const argv_;

    str simulation_input_file;
    str simulation_output_file;
    bool exit{false};
    AppState app_state_;
};

}  // namespace haf::host

#endif
