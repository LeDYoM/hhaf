#pragma once

#ifndef LIB_IRESOURCELOADER_INCLUDE_HPP
#define LIB_IRESOURCELOADER_INCLUDE_HPP

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
