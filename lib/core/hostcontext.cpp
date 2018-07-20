#include "hostcontext.hpp"
#include "host.hpp"

namespace lib::core
{
    HostContext::HostContext(Host *const host)
        : m_host{ host } { }

    const dicty::BasicDictionary<str> &HostContext::appParameters() const
    {
        return m_appParameters;
    }
}
