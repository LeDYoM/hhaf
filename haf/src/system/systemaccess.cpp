#include <haf/include/system/systemaccess.hpp>
#include <haf/include/system/isystemprovider.hpp>
#include <haf/include/system/subsystem_view.hpp>

#include "scene/scene_manager.hpp"

#include <hlog/include/hlog.hpp>

using namespace htps;

namespace haf::sys
{
SystemAccess::SystemAccess(rptr<ISystemProvider> isystem_provider) noexcept :
    isystem_provider_{std::move(isystem_provider)}
{}

SystemAccess::~SystemAccess() = default;

ISystemProvider const& SystemAccess::isystemProvider() const noexcept
{
    return *isystem_provider_;
}

ISystemProvider& SystemAccess::isystemProvider() noexcept
{
    return *isystem_provider_;
}

SubSystemViewer SystemAccess::subSystemViewer() const noexcept
{
    return SubSystemViewer{isystem_provider_};
}

}  // namespace haf::sys
