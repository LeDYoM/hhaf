#pragma once

#ifndef LIB_IAPP_INCLUDE_HPP
#define LIB_IAPP_INCLUDE_HPP

#include "windowcreationparams.hpp"
#include <lib/include/core/ihostcontext.hpp>
#include <lib/include/core/iappcontext.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib
{
    struct IAppDescriptor
    {
        const char *const configFile;
        const char *const resourceFile;
        WindowCreationParams wcp;
    };

	class IApp
	{
	public:
        constexpr IApp() : m_hostContext{ nullptr }, m_iappContext{ nullptr } { }
		virtual ~IApp() {}

        virtual void sceneFinished() {}
        virtual IAppDescriptor getAppDescriptor() const = 0;
        virtual void onInit() = 0;

        inline void setHostContext(core::IHostContext*hostContext) noexcept { m_hostContext = hostContext; }
        inline void setAppContext(core::IAppContext*appContext) noexcept { m_iappContext = appContext; }

        inline core::IHostContext &hostContext() const { return *m_hostContext; }
        inline core::IAppContext &appContext() const { return *m_iappContext; }
    private:
        core::IHostContext *m_hostContext;
        core::IAppContext *m_iappContext;
    };
}

using p_initApp = lib::IApp *(*)();
using p_finishApp = bool (*)(lib::IApp* const);

#endif
