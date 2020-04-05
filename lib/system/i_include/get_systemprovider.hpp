#pragma once

#ifndef LIB_SYSTEM_INTERNAL_GET_SYSTEM_PROVIDER_INCLUDE_HPP
#define LIB_SYSTEM_INTERNAL_GET_SYSTEM_PROVIDER_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace haf::sys
{
class ISystemProvider;
class SystemProvider;
const SystemProvider &getSystemProvider(const ISystemProvider &isystem_provider);
SystemProvider &getSystemProvider(ISystemProvider &isystem_provider);
} // namespace haf::sys

#endif
