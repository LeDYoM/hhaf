#include "system/subsystem_interface_definitions.hpp"
#include "debug_system.hpp"

#include <haf/include/profiler/imemory_data_viewer.hpp>
#include <haf/include/debug_system/idebug_variables.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(debug::IMemoryDataViewer, sys::DebugSystem)
DEFINE_SUBSYSTEM_INTERFACE(debug::IDebugVariables, sys::DebugSystem)

}  // namespace haf::sys