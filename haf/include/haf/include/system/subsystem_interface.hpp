HTPS_PRAGMA_ONCE
#ifndef HAF_SYSTEM_SYSTEM_INTERFACE_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_INTERFACE_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/system/isystem_provider.hpp>

namespace haf::sys
{
template <typename SystemInterface_t>
htps::rptr<SystemInterface_t> subSystemInterface(
    htps::rptr<ISystemProvider> const system_provider);

template <typename SystemInterface_t>
htps::rptr<SystemInterface_t const> subSystemInterface(
    htps::rptr<ISystemProvider const> const system_provider);

}  // namespace haf::sys

#endif
