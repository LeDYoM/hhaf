#include "appservice.hpp"
#include "isystemprovider.hpp"
#include "systemprovider.hpp"

namespace lib
{
AppService::AppService(sys::SystemProvider &system_provider) noexcept
        : system_provider_{system_provider} {}

AppService::~AppService() = default;

sys::SystemProvider &AppService::systemProvider() noexcept
{
    return system_provider_;
}

sys::SystemProvider const& AppService::systemProvider() const noexcept
{
    return system_provider_;
}

sys::ISystemProvider &AppService::isystemProvider() noexcept
{
    return system_provider_;
}

sys::ISystemProvider const& AppService::isystemProvider() const noexcept
{
    return system_provider_;
}

} // namespace lib
