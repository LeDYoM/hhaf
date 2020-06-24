#pragma once

#ifndef HAF_SYS_SYSTEM_ACCESS_INCLUDE_HPP
#define HAF_SYS_SYSTEM_ACCESS_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace haf::sys
{
class ISystemProvider;

class SystemAccess
{
public:
    SystemAccess(mtps::rptr<ISystemProvider> isystem_provider) noexcept;

    const ISystemProvider &isystemProvider() const noexcept;
    ISystemProvider &isystemProvider() noexcept;

    void copySystemProvider(mtps::rptr<ISystemProvider>);

private:
    mtps::rptr<ISystemProvider> isystem_provider_;
};
} // namespace haf::sys

#endif
