#ifndef HAF_HOST_PRIVATE_INCLUDE_HPP
#define HAF_HOST_PRIVATE_INCLUDE_HPP

#include "host.hpp"
#include "systemcontroller_loader.hpp"

#include "hosted_application.hpp"
#include "app_loader.hpp"
#include "host_config.hpp"
#include "app_state.hpp"
#include "hosted_app_group.hpp"
#include <haf/include/system/isystemcontroller.hpp>

#include <hlog/include/hlog.hpp>

#include <agloader/include/loader.hpp>

#include <htypes/include/vector.hpp>
#include <htypes/include/parpar.hpp>
#include <htypes/include/object.hpp>
#include <htypes/include/parpar.hpp>

#include <hosted_app/include/iapp.hpp>

#include <backend/include/backendfactory.hpp>
#include <backend/include/backend_creator.hpp>

using namespace htps;

namespace haf::host
{
class Host::HostPrivate final
{
public:
    HostPrivate(const int argc, char const* const argv[]);

    int const argc_;
    char const* const* const argv_;
    BackendFactoryUPtr backend_factory_;

    HostConfig config_;
    parpar::ParametersParser params_;
    SystemControllerLoader system_loader_;
    AppLoader app_loader;
    HostedAppGroup app_group_;

    HostedApplication& currentHostedApplication();
    HostedApplication const& currentHostedApplication() const;
    rptr<IApp const> currentApp() const;
    rptr<IApp> currentApp();

    bool initialize();

    str configuredFirstApp() const;

    AppState currentAppState() noexcept;

    bool loopStep();

    bool update();

    bool addApplication(ManagedApp managed_app, htps::str name);
    bool loadApplication(htps::str const& app_name);
    bool unloadApplication(htps::str const& app_name);

    str simulation_input_file;
    str simulation_output_file;
    bool exit{false};
private:
    rptr<haf::sys::ISystemController> systemController() noexcept;
    rptr<haf::sys::ISystemController const> systemController() const noexcept;

};

}  // namespace haf::host

#endif
