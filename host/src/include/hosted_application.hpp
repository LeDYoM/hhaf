#ifndef HAF_HOST_HOSTED_APPLICATION_INCLUDE_HPP
#define HAF_HOST_HOSTED_APPLICATION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include "app_loader.hpp"
#include <hosted_app/include/iapp.hpp>

using namespace htps;

namespace haf::host
{
class HostedApplication final
{
public:
    HostedApplication(htps::str app_name) noexcept;
    HostedApplication(htps::rptr<IApp> iapp,
                      ManagedApp managed_app,
                      str app_name) noexcept;

    htps::rptr<IApp> iapp_{nullptr};
    ManagedApp managed_app_;
    htps::str app_name_;
};

bool operator==(HostedApplication const& lhs,
                HostedApplication const& rhs) noexcept;

htps::str appDisplayNameAndVersion(const IApp& app);

}  // namespace haf::host

#endif
