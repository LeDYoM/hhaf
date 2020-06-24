#include "systemaccess.hpp"
#include "isystemprovider.hpp"

#include <scene/i_include/scenemanager.hpp>

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::sys
{
SystemAccess::SystemAccess(rptr<ISystemProvider> isystem_provider) noexcept
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
    LogAsserter::log_assert(isystem_provider_ == nullptr, "You should not use this function"
                                " if isystemProvider is already set");

    LogAsserter::log_assert(rhs != nullptr, "Parameter is nullptr");
    isystem_provider_ = std::move(rhs);
}

} // namespace haf::scene
