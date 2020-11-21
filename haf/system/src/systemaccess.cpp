#include <haf/system/include/systemaccess.hpp>
#include <haf/system/include/isystemprovider.hpp>

#include <scene/i_include/scenemanager.hpp>

#include <hlog/include/hlog.hpp>

using namespace mtps;

namespace haf::sys
{
SystemAccess::SystemAccess(rptr<ISystemProvider> isystem_provider) noexcept :
    isystem_provider_{std::move(isystem_provider)}
{}

SystemAccess::~SystemAccess() noexcept
{}

ISystemProvider const& SystemAccess::isystemProvider() const noexcept
{
    return *isystem_provider_;
}

ISystemProvider& SystemAccess::isystemProvider() noexcept
{
    return *isystem_provider_;
}

bool SystemAccess::setSystemProvider(rptr<ISystemProvider> const rhs)
{
    LogAsserter::log_assert(isystem_provider_ == nullptr,
                            "You should not use this function"
                            " if isystemProvider is already set");

    LogAsserter::log_assert(rhs != nullptr, "Parameter is nullptr");

    // Invalid data. Exit performing no action.
    if (isystem_provider_ != nullptr || rhs == nullptr)
    {
        return false;
    }

    // Valid data. Perform action and return true.
    isystem_provider_ = rhs;
    return true;
}

}  // namespace haf::sys
