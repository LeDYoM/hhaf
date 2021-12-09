#ifndef HAF_SYSTEM_SYSTEM_INTERFACE_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_INTERFACE_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/system/isystemprovider.hpp>

namespace haf::sys
{
template <typename SystemInterface_t>
types::rptr<SystemInterface_t> subSystemInterface(
    types::rptr<ISystemProvider> const system_provider);

template <typename SystemInterface_t>
types::rptr<SystemInterface_t const> subSystemInterface(
    types::rptr<ISystemProvider const> const system_provider);

}  // namespace haf::sys

#endif
