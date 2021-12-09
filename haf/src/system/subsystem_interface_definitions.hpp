#include <haf/include/system/systemaccess.hpp>
#include "get_system.hpp"

#include <haf/include/system/subsystem_interface.hpp>
#include <haf/include/system/isystemprovider.hpp>

namespace haf::sys
{
#define DEFINE_SUBSYSTEM_INTERFACE(InterfaceType, SystemType)   \
template <> \
htps::rptr<InterfaceType> subSystemInterface<InterfaceType>(  \
    htps::rptr<ISystemProvider> const isystem_provider) \
{   \
    return &(getSystem<SystemType>(isystem_provider));   \
}   \
    \
template <> \
htps::rptr<InterfaceType const> subSystemInterface<InterfaceType>(    \
    htps::rptr<ISystemProvider const> const isystem_provider)   \
{   \
    return &(getSystem<SystemType>(isystem_provider));   \
}   \

}  // namespace haf::sys
