#pragma once

#ifndef LIB_IHOSTCONTEXT_INTERFACE_INCLUDE_HPP
#define LIB_IHOSTCONTEXT_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/dicty.hpp>

namespace lib::scene
{
    class SceneManager;
}

namespace lib::core
{

    class IHostContext
    {
    public:
        virtual ~IHostContext() {}
        virtual const Dictionary<str> &appParameters() const = 0;

        virtual const scene::SceneManager &sceneManager() const noexcept = 0;
        virtual scene::SceneManager &sceneManager() noexcept = 0;

    };
}

#endif
