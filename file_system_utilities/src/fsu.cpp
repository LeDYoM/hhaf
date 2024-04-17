#include <fsu/include/fsu.hpp>
#include "driver_normal/file_driver_normal.hpp"

using namespace htps;

namespace fsu
{

FileSystem createNullFileSystem()
{
    return {};
}

FileSystem createDiskFileSystem()
{
    auto file_system{createNullFileSystem()};
    file_system.addFileDriver(htps::muptr<FileDriverNormal>());
    return file_system;

}

}  // namespace fsu
