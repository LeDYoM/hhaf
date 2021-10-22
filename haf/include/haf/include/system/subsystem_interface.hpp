#ifndef HAF_SYSTEM_SYSTEM_INTERFACE_INCLUDE_HPP
#define HAF_SYSTEM_SYSTEM_INTERFACE_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>
#include <haf/include/system/systemaccess.hpp>

namespace haf::sys
{
template <typename SystemInterface_t>
types::rptr<SystemInterface_t> subSystemInterface(
    types::rptr<SystemAccess> const system_access);

template <typename SystemInterface_t>
types::rptr<SystemInterface_t const> subSystemInterface(
    types::rptr<SystemAccess const> const system_access);
}  // namespace haf::sys

#endif
