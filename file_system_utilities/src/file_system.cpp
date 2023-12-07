#include <fsu/include/file_system.hpp>
#include <fsu/include/in_file.hpp>
#include <fsu/include/out_file.hpp>

using namespace htps;

namespace fsu
{
uptr<InFile> FileSystem::openFile(str const& fileName, OperationRead)
{
    return openFileForRead(fileName);
}

uptr<OutFile> FileSystem::openFile(str const& fileName, OperationWrite)
{
    return openFileForWriting(fileName);
}

uptr<InFile> FileSystem::openFileForRead(str const&)
{
    return htps::uptr<InFile>{};
}

uptr<OutFile> FileSystem::openFileForWriting(str const&)
{
    return htps::uptr<OutFile>{};
}

}
