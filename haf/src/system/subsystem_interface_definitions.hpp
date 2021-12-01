#include <haf/include/system/systemaccess.hpp>
#include "get_system.hpp"

#include <haf/include/system/subsystem_interface.hpp>

namespace haf::sys
{
#define DEFINE_SUBSYSTEM_INTERFACE(InterfaceType, SystemType)   \
template <> \
htps::rptr<InterfaceType> subSystemInterface<InterfaceType>(  \
    htps::rptr<SystemAccess> const system_access) \
{   \
    return &(getSystem<SystemType>(system_access));   \
}   \
    \
template <> \
htps::rptr<InterfaceType const> subSystemInterface<InterfaceType>(    \
    htps::rptr<SystemAccess const> const system_access)   \
{   \
    return &(getSystem<SystemType>(system_access));   \
}   \

}  // namespace haf::sys
