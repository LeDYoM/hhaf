#include "appcontext.hpp"
#include "host.hpp"

namespace lib::core
{
    namespace
    {
        constexpr char AppName[]            = "ApplicationName";
        constexpr char AppVersion[]         = "ApplicationVersion";
        constexpr char AppSubVersion[]      = "ApplicationSubVersion";
        constexpr char AppPatch[]           = "ApplicationPatch";


    }
    AppContext::AppContext(Host * const host) : m_host{ host } { }

    void AppContext::setApplicationName(str appName)
    {
        m_propertiesMap[AppName] = str(appName);
    }

    void AppContext::setApplicationVersion(size_type version)
    {
        m_propertiesMap[AppVersion] = make_str(version);
    }

    void AppContext::setApplicationSubVersion(size_type subversion)
    {
        m_propertiesMap[AppSubVersion] = make_str(subversion);
    }

    void AppContext::setApplicationPatch(size_type patch)
    {
        m_propertiesMap[AppPatch] = make_str(patch);
    }

    str AppContext::appId() const
    {
        return make_str(m_propertiesMap.at(AppName), ":", m_propertiesMap.at(AppVersion), ".",
            m_propertiesMap.at(AppSubVersion), ".", m_propertiesMap.at(AppPatch));
    }
    void AppContext::setProperty(str prop_name, str prop_value)
    {
    }
}
