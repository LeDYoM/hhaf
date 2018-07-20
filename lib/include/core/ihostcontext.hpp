#pragma once

#ifndef LIB_IHOSTCONTEXT_INTERFACE_INCLUDE_HPP
#define LIB_IHOSTCONTEXT_INTERFACE_INCLUDE_HPP

#include <lib/include/lib.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/dicty.hpp>

namespace lib::core
{
    class IHostContext
    {
    public:
        virtual const dicty::BasicDictionary<str> &appParameters() const = 0;
    };
}

#endif
