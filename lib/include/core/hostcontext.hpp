#pragma once

#ifndef LIB_HOSTCONTEXT_INCLUDE_HPP__
#define LIB_HOSTCONTEXT_INCLUDE_HPP__

#include <lib/include/lib.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/dicty.hpp>

namespace lib::core
{
    class LIB_API HostContext final
    {
    public:
        const dicty::BasicDictionary<str> &appParameters() const
        {
            return m_appParameters;
        }
    private:
        dicty::BasicDictionary<str> m_appParameters;
    };
}

#endif
