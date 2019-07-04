#pragma once

#ifndef LIB_IAPP_INCLUDE_HPP
#define LIB_IAPP_INCLUDE_HPP

#include "windowcreationparams.hpp"
#include <lib/include/core/iappcontext.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::core
{
    class SystemProvider;
}

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
        constexpr IApp() noexcept {}
        virtual ~IApp() {}

        virtual IAppDescriptor getAppDescriptor() const = 0;
        virtual void onInit() = 0;

        inline void setSystemProvider(core::SystemProvider* const system_provider) noexcept { system_provider_ = system_provider; }
        inline void setAppContext(core::IAppContext* const appContext) noexcept { m_iappContext = appContext; }

        inline core::SystemProvider &systemProvider() const noexcept { return *system_provider_; }
        inline core::IAppContext &appContext() const noexcept { return *m_iappContext; }
    private:
        core::SystemProvider *system_provider_{nullptr};
        core::IAppContext *m_iappContext{nullptr};
    };
}

using p_initApp = lib::IApp *(*)();
using p_finishApp = bool (*)(lib::IApp* const);

#endif
