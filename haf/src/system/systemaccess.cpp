#include <haf/include/system/systemaccess.hpp>
#include <haf/include/system/isystemprovider.hpp>

#include "scene/scenemanager.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{
SystemAccess::SystemAccess(rptr<ISystemProvider> isystem_provider) noexcept :
    isystem_provider_{std::move(isystem_provider)}
{}

SystemAccess::~SystemAccess()
{}

ISystemProvider const& SystemAccess::isystemProvider() const noexcept
{
    return *isystem_provider_;
}

ISystemProvider& SystemAccess::isystemProvider() noexcept
{
    return *isystem_provider_;
}

}  // namespace haf::sys
