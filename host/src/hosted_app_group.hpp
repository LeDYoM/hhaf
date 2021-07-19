#ifndef HAF_HOST_HOSTED_APP_GROUP_PRIVATE_INCLUDE_HPP
#define HAF_HOST_HOSTED_APP_GROUP_PRIVATE_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>
#include "hosted_application.hpp"
#include "app_loader.hpp"

namespace haf::host
{
class HostConnector;
class HostedAppGroup final
{
public:
    htps::vector<HostedApplication> app_;
    htps::u32 index_current_app{0U};

    HostedApplication& currentHostedApplication();
    HostedApplication const& currentHostedApplication() const;
    htps::rptr<IApp const> currentApp() const;
    htps::rptr<IApp> currentApp();

    void setCurrentAppState(AppState const app_state) noexcept;

    bool try_add_app(ManagedApp managed_app,
                     htps::str name,
                     htps::uptr<HostConnector> host_connector);
    bool removeApp(htps::str const& app_name);
    bool appExists(htps::str const& name) noexcept;

    /**
     * @brief Get the App By Name object
     *
     * @param app_name
     * @return iterator pointing to the app with the specified
     * name. If the app was not found, dereferencing it is UB.
     */
    auto getAppByName(htps::str const& app_name)
    {
        return app_.find_if([&app_name](HostedApplication const& app) {
            return app.app_name_ == app_name;
        });
    }

private:
    void add_app(ManagedApp&& app,
                 htps::str name,
                 htps::uptr<HostConnector> host_connector);
};

}  // namespace haf::host

#endif
