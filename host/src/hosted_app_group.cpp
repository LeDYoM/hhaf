#include "hosted_app_group.hpp"
#include "host_connector.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::host
{
HostedApplication& HostedAppGroup::currentHostedApplication()
{
    return app_[index_current_app];
}

HostedApplication const& HostedAppGroup::currentHostedApplication() const
{
    return app_[index_current_app];
}

rptr<IApp const> HostedAppGroup::currentApp() const
{
    return app_[index_current_app].managed_app_.app;
}

rptr<IApp> HostedAppGroup::currentApp()
{
    return app_[index_current_app].managed_app_.app;
}

void HostedAppGroup::setCurrentAppState(AppState const app_state) noexcept
{
    currentHostedApplication().app_state = app_state;
}

bool HostedAppGroup::try_add_app(ManagedApp managed_app,
                                 str name,
                                 uptr<HostConnector> host_connector)
{
    LogAsserter::log_assert(managed_app.app != nullptr,
                            "Received nullptr Application");

    // Store if the app is not already registered
    bool const is_new_app{!appExists(name)};

    DisplayLog::error_if(!is_new_app, "Application already registered");

    if (is_new_app)
    {
        DisplayLog::info("Starting Registering app...");
        auto& new_app = add_app(std::move(managed_app), std::move(name),
                std::move(host_connector));
        DisplayLog::verbose("Starting new app...");
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
        DisplayLog::info_if(old_size != new_size, "Application ", app_name,
                            " unloaded");

        DisplayLog::info_if(old_size == new_size, "Application ", app_name,
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

HostedApplication& HostedAppGroup::back()
{
    return app_.back();
}

bool HostedAppGroup::appExists(str const& name) noexcept
{
    // Search for a pointer to the same app
    return (app_.cfind(HostedApplication{ManagedApp{}, name, nullptr}) !=
            app_.cend());
}

HostedApplication& HostedAppGroup::add_app(ManagedApp&& app,
                                           str name,
                                           uptr<HostConnector> host_connector)
{
    app_.emplace_back(std::move(app), std::move(name),
                      std::move(host_connector));
    return app_.back();
}

}  // namespace haf::host
