#ifndef HAF_HOST_INTERNAL_INCLUDE_HPP
#define HAF_HOST_INTERNAL_INCLUDE_HPP

#include "host.hpp"
#include "systemcontroller_loader.hpp"
#include "hosted_application.hpp"
#include "app_loader.hpp"
#include "host_config.hpp"
#include "app_state.hpp"
#include "hosted_app_group.hpp"

#include <haf/include/system/isystemcontroller.hpp>
#include <htypes/include/parpar.hpp>
#include <hosted_app/include/iapp.hpp>
#include <backend/include/backend_creator.hpp>

namespace haf::host
{
class HostInternal
{
public:
    HostInternal(const int argc, char const* const argv[]);

    int const argc_;
    char const* const* const argv_;
    BackendFactoryUPtr backend_factory_;

    HostConfig config_;
    parpar::ParametersParser params_;
    SystemControllerLoader system_loader_;
    AppLoader app_loader;
    HostedAppGroup app_group_;

    bool initialize();

    htps::str configuredFirstApp() const;

    bool update();

    bool addApplication(ManagedApp managed_app, htps::str name);
    bool loadApplication(htps::str const& app_name);
    bool unloadApplication(htps::str const& app_name);
    bool unloadAllApplications();

    htps::str simulation_input_file;
    htps::str simulation_output_file;
    bool exit{false};

private:
    bool updateApp(HostedApplication& app);
    bool initializeBackend();
    bool initializeHaf();
};

}  // namespace haf::host

#endif
