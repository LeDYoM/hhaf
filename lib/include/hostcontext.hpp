#ifndef LIB_HOSTCONTEXT_INCLUDE_HPP__
#define LIB_HOSTCONTEXT_INCLUDE_HPP__

#include "compconfig.hpp"
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/dicty.hpp>

namespace lib
{
    class HostContext final
    {
    public:
        const BasicDictionary &appParameters() const
        {
            return m_appParameters;
        }
    private:
        BasicDictionary m_appParameters;
    };
}

#endif
