#pragma once

#ifndef LIB_IAPPCONTEXT_INTERFACE_INCLUDE_HPP
#define LIB_IAPPCONTEXT_INTERFACE_INCLUDE_HPP

#include <lib/include/lib.hpp>
#include <mtypes/include/types.hpp>

namespace lib::core
{
    class IAppContext
    {
    public:
        virtual void setApplicationName(const char*const appName) = 0;
        virtual void setApplicationVersion(size_type version) = 0;
        virtual void setApplicationSubVersion(size_type subversion) = 0;
        virtual void setApplicationPatch(size_type patch) = 0;
    };
}

#endif
