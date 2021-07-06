#ifndef HAF_HOST_HOSTED_APP_GROUP_PRIVATE_INCLUDE_HPP
#define HAF_HOST_HOSTED_APP_GROUP_PRIVATE_INCLUDE_HPP

#include <htypes/include/vector.hpp>
#include <host/include/host.hpp>
#include "hosted_application.hpp"
#include "app_loader.hpp"

namespace haf::host
{
class HostedAppGroup final
{
public:
    htps::vector<HostedApplication> app_;
    htps::u32 index_current_app{0U};

    HostedApplication& currentHostedApplication();
    HostedApplication const& currentHostedApplication() const;
    rptr<IApp const> currentApp() const;
    rptr<IApp> currentApp();

};

}  // namespace haf::host

#endif
