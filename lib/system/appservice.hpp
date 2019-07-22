#pragma once

#ifndef LIB_APP_SERVICE_INCLUDE_HPP
#define LIB_APP_SERVICE_INCLUDE_HPP

namespace lib::core
{
    class SystemProvider;
}

namespace lib
{
    /**
    * Class to serve as a base for all App Services.
    * 
    * An App Service is a class, instanciated by SystemProvider to give functionality
    * to the app clients.
    */
    class AppService
    {
    protected:
        AppService() = default;
        AppService(const AppService &rh) = delete;
        AppService &operator=(const AppService &rh) = delete;

        virtual ~AppService() = default;
    };

    class HostedAppService : public AppService
    {
    protected:
        constexpr HostedAppService(core::SystemProvider &system_provider) noexcept
            : AppService{}, system_provider_ { system_provider } {}

        ~HostedAppService() override = default;

    public:
        constexpr core::SystemProvider& systemProvider() noexcept { return system_provider_; }
        constexpr const core::SystemProvider& systemProvider() const noexcept { return system_provider_; }

    private:
        core::SystemProvider &system_provider_;
    };
}

#endif
