#pragma once

#ifndef LIB_SCENE_SYSTEM_ACCESS_INCLUDE_HPP
#define LIB_SCENE_SYSTEM_ACCESS_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace lib::sys
{
class ISystemProvider;

class SystemAccess
{
public:
    SystemAccess(mtps::rptr<ISystemProvider> isystem_provider);

    const ISystemProvider &isystemProvider() const noexcept;
    ISystemProvider &isystemProvider() noexcept;

    void copySystemProvider(mtps::rptr<ISystemProvider>);

private:
    mtps::rptr<ISystemProvider> isystem_provider_;
};
} // namespace lib::sys

#endif
