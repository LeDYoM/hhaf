#include "system/subsystem_interface_definitions.hpp"
#include "file_system.hpp"

#include <haf/include/filesystem/ifile_serializer.hpp>

namespace haf::sys
{
DEFINE_SUBSYSTEM_INTERFACE(sys::IFileSerializer, sys::FileSystem)

}  // namespace haf::sys
