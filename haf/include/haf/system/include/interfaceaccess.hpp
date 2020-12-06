#ifndef HAF_SYS_INTERFACE_ACCESS_INCLUDE_HPP
#define HAF_SYS_INTERFACE_ACCESS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "systemaccess.hpp"

namespace haf::sys
{

template <typename T>
T& getInterface(SystemAccess&);

template <typename T>
T const& getInterface(SystemAccess const&);

}  // namespace haf::sys

#endif
