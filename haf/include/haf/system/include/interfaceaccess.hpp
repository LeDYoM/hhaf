#pragma once

#ifndef HAF_SYS_INTERFACE_ACCESS_INCLUDE_HPP
#define HAF_SYS_INTERFACE_ACCESS_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include "systemaccess.hpp"

namespace haf::sys
{
class ISystemProvider;

template<typename T>
T& getInterface(ISystemProvider&);

} // namespace haf::sys

#endif
