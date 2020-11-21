#include <system/i_include/get_systemprovider.hpp>
#include <system/i_include/systemprovider.hpp>
#include <haf/system/include/isystemprovider.hpp>

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
