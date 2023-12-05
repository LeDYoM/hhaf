#include <fsu/include/file_system.hpp>

using namespace htps;

namespace fsu
{
uptr<InFile> FileSystem::openFile(str const& fileName, OperationRead)
{
    return openFileForRead(fileName);
}

uptr<OutFile> oFileSystem::penFile(htps::str const& fileName, OperationWrite)
{
    return openFile
}

uptr<InFile> FileSystem::openFileForRead(htps::str const& fileName)
{
    return htps::uptr<InFile>{};
}

uptr<OutFile> FileSystem::openFileForWriting(htps::str const& fileName)
{
    return htps::uptr<OutFile>{};
}

}
