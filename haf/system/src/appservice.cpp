#include "appservice.hpp"
#include "isystemprovider.hpp"
#include "systemprovider.hpp"

namespace haf::sys
{
AppService::AppService(sys::ISystemProvider& system_provider) noexcept :
    system_provider_{system_provider}
{}

AppService::~AppService() = default;

SystemProvider& AppService::systemProvider() noexcept
{
    return dynamic_cast<SystemProvider&>(system_provider_);
}

SystemProvider const& AppService::systemProvider() const noexcept
{
    return dynamic_cast<SystemProvider&>(system_provider_);
}

ISystemProvider& AppService::isystemProvider() noexcept
{
    return system_provider_;
}

ISystemProvider const& AppService::isystemProvider() const noexcept
{
    return system_provider_;
}

}  // namespace haf::sys
