#pragma once

#ifndef LIB_APPCONTEXT_INCLUDE_HPP
#define LIB_APPCONTEXT_INCLUDE_HPP

#include <lib/include/lib.hpp>
#include <lib/include/core/iappcontext.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::core
{
    class Host;
    class AppContext final : public IAppContext
    {
    public:
        explicit AppContext(Host *const host);
        void setApplicationName(const char*const appName) override;
        void setApplicationVersion(size_type version) override;
        void setApplicationSubVersion(size_type subversion) override;
        void setApplicationPatch(size_type patch) override;
        str appId() const;
    private:
        Host * m_host{ nullptr };
        str m_applicationName{ "UnknownApp" };
        size_type m_applicationVersion{ 0U };
        size_type m_applicationSubVersion{ 0U };
        size_type m_applicationPatch{ 0U };
    };
}

#endif
