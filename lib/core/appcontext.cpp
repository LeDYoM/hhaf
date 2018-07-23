#include "appcontext.hpp"
#include "host.hpp"

namespace lib::core
{
    AppContext::AppContext(Host * const host) : m_host{ host }
    { }

    void AppContext::setApplicationName(const char * const appName)
    {
        m_applicationName = str(appName);
    }

    void AppContext::setApplicationVersion(size_type version)
    {
        m_applicationVersion = version;
    }

    void AppContext::setApplicationSubVersion(size_type subversion)
    {
        m_applicationSubVersion = subversion;
    }

    void AppContext::setApplicationPatch(size_type patch)
    {
        m_applicationPatch = patch;
    }

    str AppContext::appId() const
    {
        return make_str(m_applicationName, ":", m_applicationVersion, ".", 
            m_applicationSubVersion, ".", m_applicationPatch);
    }
}
