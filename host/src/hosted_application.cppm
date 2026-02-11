module;

#include <hosted_app/include/iapp.hpp>
#include <host_connector/include/ihost_connector.hpp>
#include <host_haf_interface/include/isystem_controller.hpp>

export module host:hosted_application;

import :app_loader;
import :app_state;

import htypes;

namespace haf::host
{
class HostedApplication final
{
public:
    HostedApplication(ManagedApp managed_app,
                      htps::str app_name,
                      htps::uptr<IHostConnector> host_connector) noexcept :
        managed_app_{htps::move(managed_app)},
        app_name_{htps::move(app_name)},
        host_connector_{htps::move(host_connector)}
    {}

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

    bool operator==(HostedApplication const& rhs) const noexcept
    {
        return app_name_ == rhs.app_name_;
    }
};

htps::str appDisplayNameAndVersion(IApp const& app)
{
    return make_str(app.getName(), "(", app.getVersion(), ".",
                    app.getSubVersion(), ".", app.getPatch(), ")");
}

htps::str appDisplayNameAndVersion(ManagedApp const& app)
{
    return appDisplayNameAndVersion(*(app.app));
}

htps::str appDisplayNameAndVersion(HostedApplication const& app)
{
    return appDisplayNameAndVersion(app.managed_app_);
}

}  // namespace haf::host
