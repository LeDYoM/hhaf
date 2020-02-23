#pragma once

#ifndef LIB_APP_SERVICE_INCLUDE_HPP
#define LIB_APP_SERVICE_INCLUDE_HPP

namespace lib::sys
{
class SystemProvider;
}

namespace lib
{
/**
 * @brief Class to serve as a base for all App Services.
 * An App Service is a class, instanciated by SystemProvider to give
 * functionality to the app clients.
 */
class HostedAppService
{
protected:
    constexpr HostedAppService(sys::SystemProvider &system_provider) noexcept
        : system_provider_{system_provider} {}

    virtual ~HostedAppService() = default;

public:
    HostedAppService(const HostedAppService &rh) = delete;
    HostedAppService &operator=(const HostedAppService &rh) = delete;

    constexpr sys::SystemProvider &systemProvider() noexcept
    { 
        return system_provider_;
    }

    constexpr const sys::SystemProvider &systemProvider() const noexcept
    { 
        return system_provider_;
    }

private:
    sys::SystemProvider &system_provider_;
};
} // namespace lib

#endif
