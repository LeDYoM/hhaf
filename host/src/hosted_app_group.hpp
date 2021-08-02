#ifndef HAF_HOST_HOSTED_APP_GROUP_INCLUDE_HPP
#define HAF_HOST_HOSTED_APP_GROUP_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>
#include "hosted_application.hpp"

namespace haf::host
{
class HostConnector;
class HostedAppGroup final
{
public:

    bool try_add_app(ManagedApp managed_app,
                     htps::str name,
                     htps::uptr<HostConnector> host_connector);
    bool removeApp(htps::str const& app_name);
    bool appExists(htps::str const& name) noexcept;

    /**
     * @brief Get the App By Name object
     *
     * @param app_name Name of the application to search
     * @return iterator pointing to the app with the specified
     * name. If the app was not found, dereferencing it is UB.
     */
    auto operator[](htps::str const& app_name)
    {
        return app_.find_if([&app_name](HostedApplication const& app) {
            return app.app_name_ == app_name;
        });
    }

    bool empty() const noexcept;
    htps::size_type size() const noexcept;
    HostedApplication& back();

    auto begin() const noexcept { return app_.begin(); }

    auto begin() noexcept { return app_.begin(); }

    auto end() const noexcept { return app_.end(); }

    auto end() noexcept { return app_.end(); }

private:
    htps::vector<HostedApplication> app_;
    htps::u32 index_current_app{0U};

    HostedApplication& add_app(ManagedApp&& app,
                               htps::str name,
                               htps::uptr<HostConnector> host_connector);
};

}  // namespace haf::host

#endif
