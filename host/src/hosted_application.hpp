#ifndef HAF_HOST_HOSTED_APPLICATION_INCLUDE_HPP
#define HAF_HOST_HOSTED_APPLICATION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include "app_loader.hpp"
#include "app_state.hpp"
#include <hosted_app/include/iapp.hpp>
#include <host_connector/include/ihost_connector.hpp>
#include <haf/include/system/isystem_controller.hpp>

namespace haf::host
{
class HostedApplication final
{
public:
    HostedApplication(ManagedApp managed_app,
                      htps::str app_name,
                      htps::uptr<IHostConnector> host_connector) noexcept;

    ManagedApp managed_app_;
    htps::str app_name_;
    htps::uptr<IHostConnector> host_connector_;
    sys::UptrSystemController app_system_controller;
    AppState app_state{AppState::NotInitialized};

    /**
     * @brief Deleted copy constructor
     */
    HostedApplication(HostedApplication const&) = delete;

    /**
     * @brief Deleted copy assignment
     */
    HostedApplication& operator=(HostedApplication const&) = delete;

    /**
     * @brief Defaulted move constructor
     */
    HostedApplication(HostedApplication&&) = default;

    /**
     * @brief Defaulted move assignment
     */
    HostedApplication& operator=(HostedApplication&&) = default;
};

bool operator==(HostedApplication const& lhs,
                HostedApplication const& rhs) noexcept;

htps::str appDisplayNameAndVersion(IApp const& app);
htps::str appDisplayNameAndVersion(ManagedApp const& app);
htps::str appDisplayNameAndVersion(HostedApplication const& app);

}  // namespace haf::host

#endif
