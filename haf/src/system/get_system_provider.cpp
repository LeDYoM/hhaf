#include "system/get_system_provider.hpp"
#include "system/system_provider.hpp"

#include <haf/include/system/isystem_provider.hpp>

namespace haf::sys
{
const sys::SystemProvider& getSystemProvider(
    const sys::ISystemProvider& isystem_provider)
{
    return dynamic_cast<const sys::SystemProvider&>(isystem_provider);
}

sys::SystemProvider& getSystemProvider(sys::ISystemProvider& isystem_provider)
{
    return dynamic_cast<sys::SystemProvider&>(isystem_provider);
}

}  // namespace haf::sys
