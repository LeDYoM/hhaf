#ifndef HAF_DEBUG_DEBUG_SYSTEM_INCLUDE_HPP
#define HAF_DEBUG_DEBUG_SYSTEM_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include "system/systembase.hpp"

namespace haf::sys
{
class DebugSystem final : public SystemBase
{
    using BaseClass = SystemBase;

public:
    using BaseClass::BaseClass;
    ~DebugSystem();
};

}  // namespace haf::sys

#endif
