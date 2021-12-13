#include "system/subsystem_interface_definitions.hpp"
#include "time_system.hpp"

#include <haf/include/time/time_view.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(time::ITimeView, sys::TimeSystem)

}  // namespace haf::sys
