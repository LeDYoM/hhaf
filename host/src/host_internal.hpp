#ifndef HAF_HOST_INTERNAL_INCLUDE_HPP
#define HAF_HOST_INTERNAL_INCLUDE_HPP

#include "host.hpp"
#include "systemcontroller_loader.hpp"
#include "hosted_application.hpp"
#include "app_loader.hpp"
#include "host_config.hpp"
#include "app_state.hpp"
#include "hosted_app_group.hpp"

#include <haf/include/system/isystem_controller.hpp>
#include <htypes/include/parpar.hpp>
#include <hosted_app/include/iapp.hpp>
#include <backend/include/backend_creator.hpp>

namespace haf::host
{
class HostInternal
{
public:
    static constexpr char StaticTypeName[] = "HostInternal";

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

    /**
     * @brief Performs the main update cycle, updating all current active
     * applications.
     *
     * @return true The host wants to exit
     * @return false The host wants to continue
     */
    bool update();

    bool addApplication(ManagedApp managed_app, htps::str name);
    bool loadApplication(htps::str const& app_name);
    bool unloadApplication(htps::str app_name);
    bool unloadAllApplications();

    htps::str simulation_input_file;
    htps::str simulation_output_file;
    bool exit{false};

private:
    /**
     * @brief Updates a given @b HostApplication, performing actions
     * depending on which state the application currently is.
     *
     * @param app Application to update
     * @return true The application wants to exit
     * @return false The application wants to continue executing
     */
    bool updateApp(HostedApplication& app);
    bool initializeBackend();
    void logLoadedFactories();
    bool initializeHaf();
};

}  // namespace haf::host

#endif
