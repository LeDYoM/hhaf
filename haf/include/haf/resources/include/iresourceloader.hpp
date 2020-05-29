#pragma once

#ifndef HAF_IRESOURCELOADER_INCLUDE_HPP
#define HAF_IRESOURCELOADER_INCLUDE_HPP

#include <mtypes/include/str.hpp>

namespace haf
{
    class IResourceHandler;

    class IResourceLoader
    {
    public:
        virtual void loadResources(IResourceHandler&) = 0;
    };
}

#endif
