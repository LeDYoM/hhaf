#include "system_base.hpp"
#include "system_provider.hpp"

#include <haf/include/system/isystem_provider.hpp>
#include <haf/include/system/system_access.hpp>
#include <haf/include/system/subsystem_view.hpp>

using namespace htps;

namespace haf::sys
{
SystemBase::SystemBase(sys::ISystemProvider& system_provider) noexcept :
    system_provider_{system_provider}
{}

SystemBase::~SystemBase() noexcept = default;

SystemProvider& SystemBase::systemProvider() noexcept
{
    return dynamic_cast<SystemProvider&>(system_provider_);
}

SystemProvider const& SystemBase::systemProvider() const noexcept
{
    return dynamic_cast<SystemProvider&>(system_provider_);
}

ISystemProvider& SystemBase::isystemProvider() noexcept
{
    return system_provider_;
}

ISystemProvider const& SystemBase::isystemProvider() const noexcept
{
    return system_provider_;
}

SystemAccess SystemBase::systemAccess() noexcept
{
    return *systemAccessPtr();
}

rptr<SystemAccess> SystemBase::systemAccessPtr() noexcept
{
    system_access_ = muptr<SystemAccess>(&(isystemProvider()));
    return system_access_.get();
}

SubSystemViewer SystemBase::subSystemViewer() noexcept
{
    (void)(systemAccess());
    return SubSystemViewer{&system_provider_};
}

}  // namespace haf::sys
