#pragma once

#ifndef LIB_HOSTCONTEXT_INCLUDE_HPP
#define LIB_HOSTCONTEXT_INCLUDE_HPP

#include <lib/include/core/ihostcontext.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/dicty.hpp>

namespace lib::scene
{
    class SceneManager;
}

namespace lib::core
{
    class Host;
    class HostContext final : public IHostContext
    {
    public:
        explicit HostContext(Host *const host);
        const Dictionary<str> &appParameters() const override;

        const scene::SceneManager &sceneManager() const noexcept override;
        scene::SceneManager &sceneManager() noexcept override;

    private:
        Host *const m_host;
        Dictionary<str> m_appParameters;
    };
}

#endif
