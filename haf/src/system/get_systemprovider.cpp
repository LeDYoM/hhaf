#include "system/get_systemprovider.hpp"
#include "system/systemprovider.hpp"

#include <haf/include/system/isystemprovider.hpp>

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
