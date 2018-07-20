#pragma once

#ifndef LIB_HOSTCONTEXT_INCLUDE_HPP
#define LIB_HOSTCONTEXT_INCLUDE_HPP

#include <lib/include/lib.hpp>
#include <lib/include/core/ihostcontext.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/dicty.hpp>

namespace lib::core
{
    class Host;
    class HostContext final : public IHostContext
    {
    public:
        explicit HostContext(Host *const host);
        const dicty::BasicDictionary<str> &appParameters() const override;
    private:
        Host *const m_host;
        dicty::BasicDictionary<str> m_appParameters;
    };
}

#endif
