#pragma once

#ifndef LIB_APPCONTEXT_INCLUDE_HPP
#define LIB_APPCONTEXT_INCLUDE_HPP

#include <lib/include/lib.hpp>
#include <lib/include/core/iappcontext.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <map>

namespace lib::core
{
    class Host;
    class AppContext final : public IAppContext
    {
    public:
        explicit AppContext(Host *const host);
        void setApplicationName(str appName) override;
        void setApplicationVersion(size_type version) override;
        void setApplicationSubVersion(size_type subversion) override;
        void setApplicationPatch(size_type patch) override;
        str appId() const;
        void setProperty(str prop_name, str prop_value) override;

    private:
        Host * m_host{ nullptr };
        str m_applicationName{ "UnknownApp" };
        size_type m_applicationVersion{ 0U };
        size_type m_applicationSubVersion{ 0U };
        size_type m_applicationPatch{ 0U };
        std::map<str, str> m_propertiesMap;
    };
}

#endif
