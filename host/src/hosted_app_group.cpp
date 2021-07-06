#include "hosted_app_group.hpp"

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

}  // namespace haf::host
