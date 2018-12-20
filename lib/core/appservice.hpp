#pragma once

#ifndef LIB_APP_SERVICE_INCLUDE_HPP
#define LIB_APP_SERVICE_INCLUDE_HPP

///////////////////////////////
// Temporary
#include "host.hpp"
#include "systemprovider.hpp"
///////////////////////////////

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
	protected:
        constexpr AppService(core::Host &host) noexcept : m_host{ host } {}

        AppService(const AppService &rh) = delete;
		AppService &operator=(const AppService &rh) = delete;

        virtual ~AppService() = default;

    public:
        constexpr core::Host& host() noexcept { return m_host; }
        constexpr const core::Host& host() const noexcept { return m_host; }

        constexpr core::SystemProvider& systemProvider() noexcept { return m_host; }
        constexpr const core::SystemProvider& systemProvider() const noexcept { return m_host; }

    private:
        core::Host &m_host;
	};
}
#endif
