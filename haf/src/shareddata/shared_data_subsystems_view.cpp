#include "system/subsystem_interface_definitions.hpp"
#include "shared_data_system.hpp"

#include <haf/include/shareddata/ishared_data.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(shdata::ISharedData, sys::SharedDataSystem)

}  // namespace haf::sys
