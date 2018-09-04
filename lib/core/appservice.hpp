#pragma once

#ifndef LIB_APP_SERVICE_INCLUDE_HPP
#define LIB_APP_SERVICE_INCLUDE_HPP

namespace lib
{
	namespace core
	{
		class Host;
	}

    /**
    * Class to serve as a base for all App Services.
    * 
    * An App Service is a class, instanciated by the Host to give functionality
    * to the app clients.
    */
	class AppService
	{
	public:
        constexpr AppService(core::Host &host) noexcept : m_host{ host } {}

        AppService(const AppService &rh) = delete;
		AppService &operator=(const AppService &rh) = delete;

        virtual ~AppService() = default;

        constexpr core::Host& host() noexcept { return m_host; }
        constexpr const core::Host& host() const noexcept { return m_host; }

    private:
        core::Host &m_host;
	};
}
#endif
