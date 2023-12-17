#include <fsu/include/fsu.hpp>

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
    return file_system;

}

}  // namespace fsu
