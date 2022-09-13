#include "system/subsystem_interface_definitions.hpp"
#include "debug_system.hpp"

#include <haf/include/profiler/imemory_data_viewer.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(debug::IMemoryDataViewer, sys::DebugSystem)

}  // namespace haf::sys
