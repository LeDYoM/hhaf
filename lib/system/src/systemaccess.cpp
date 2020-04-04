#include "systemaccess.hpp"
#include "scenemanager.hpp"

#include <lib/system/include/isystemprovider.hpp>
#include <lib/include/liblog.hpp>

using namespace mtps;

namespace lib::sys
{
SystemAccess::SystemAccess(rptr<ISystemProvider> isystem_provider)
    : isystem_provider_{std::move(isystem_provider)} {}

const ISystemProvider& SystemAccess::isystemProvider() const noexcept
{
    return *isystem_provider_;
}

ISystemProvider& SystemAccess::isystemProvider() noexcept
{
    return *isystem_provider_;
}

void SystemAccess::copySystemProvider(rptr<ISystemProvider> rhs)
{
    log_assert(isystem_provider_ == nullptr, "You should not use this function"
                                " if isystemProvider is already set");

    log_assert(rhs != nullptr, "Parameter is nullptr");
    isystem_provider_ = std::move(rhs);
}

} // namespace lib::scene
