#include "hostcontext.hpp"
#include "host.hpp"

#include <lib/scene/scenemanager.hpp>

namespace lib::core
{
    HostContext::HostContext(Host *const host)
        : m_host{ host } { }

    const Dictionary<str> &HostContext::appParameters() const
    {
        return m_appParameters;
    }

    const scene::SceneManager & HostContext::sceneManager() const noexcept
    {
        return m_host->sceneManager();
    }

    scene::SceneManager & HostContext::sceneManager() noexcept
    {
        return m_host->sceneManager();
    }
}
