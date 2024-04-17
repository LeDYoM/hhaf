FSU_PRAGMA_ONCE
#ifndef FSU_FSU_MAIN_INCLUDE_HPP
#define FSU_FSU_MAIN_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <fsu/include/file_system.hpp>

namespace fsu
{
FileSystem createNullFileSystem();
FileSystem createDiskFileSystem();

}  // namespace fsu

#endif
