#pragma once

#ifndef LIB_IAPP_INCLUDE_HPP__
#define LIB_IAPP_INCLUDE_HPP__

#include "windowcreationparams.hpp"
#include <lib/include/core/hostcontext.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib
{
    struct IAppDescriptor
    {
        const str Name;
        u32 Version;
        u32 SubVersion;
        u32 Patch;
        const char *const configFile;
        const char *const resourceFile;
        WindowCreationParams wcp;
    };

	class IApp
	{
	public:
		constexpr IApp() : m_hostContext{ nullptr } {}
		virtual ~IApp() {}

		inline void setHostContext(core::HostContext*hs) noexcept { m_hostContext = hs; }

        virtual void sceneFinished() {}
        virtual IAppDescriptor getAppDescriptor() const = 0;
        virtual void onInit() = 0;
        virtual int loop() = 0;

private:
        core::HostContext *m_hostContext;
    };
}

#endif
