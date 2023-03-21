#include "hosted_app_group.hpp"
#include "host_connector.hpp"
#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::host
{
bool HostedAppGroup::try_add_app(ManagedApp managed_app,
                                 str name,
                                 uptr<HostConnector> host_connector)
{
    LogAsserter::log_assert(managed_app.app != nullptr,
                            "Received nullptr Application");

    // Store if the app is not already registered
    bool const is_new_app{!appExists(name)};

    DisplayLog::error_if(!is_new_app, StaticTypeName,
                         ": Application already registered");

    if (is_new_app)
    {
        DisplayLog::info(StaticTypeName, ": Starting Registering app...");
        auto& new_app = add_app(htps::move(managed_app), htps::move(name),
                                htps::move(host_connector));
        DisplayLog::verbose(StaticTypeName, ": Starting new app...");
        new_app.app_state = AppState::ReadyToStart;
    }

    return is_new_app;
}

bool HostedAppGroup::removeApp(str const& app_name)
{
    // If the app is found, remove it from the group
    if (auto const app_iterator{(*this)[app_name]}; app_iterator != app_.end())
    {
        // Aplication found. Execute unload steps.
        auto const old_size = app_.size();

        // Remove the application from the list
        app_.erase_iterator(app_iterator, app_.end());

        auto const new_size{app_.size()};

        // Show logs informing the user
        DisplayLog::info_if(old_size != new_size, StaticTypeName,
                            ": Application ", app_name, " unloaded");

        DisplayLog::info_if(old_size == new_size, StaticTypeName,
                            ": Application ", app_name,
                            " unloaded, but cannot be deleted");

        return true;
    }

    return false;
}

bool HostedAppGroup::empty() const noexcept
{
    return app_.empty();
}

size_type HostedAppGroup::size() const noexcept
{
    return app_.size();
}

HostedApplication& HostedAppGroup::front()
{
    return *(app_.begin());
}

HostedApplication& HostedAppGroup::back()
{
    return app_.back();
}

bool HostedAppGroup::appExists(str const& name) noexcept
{
    // Search for a pointer to the same app
    return (app_.cfind(HostedApplication{ManagedApp{}, name, htps::uptr<IHostConnector>{nullptr}}) !=
            app_.cend());
}

HostedApplication& HostedAppGroup::add_app(ManagedApp&& app,
                                           str name,
                                           uptr<HostConnector> host_connector)
{
    app_.emplace_back(htps::move(app), htps::move(name),
                      htps::move(host_connector));
    return app_.back();
}

}  // namespace haf::host
