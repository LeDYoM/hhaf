#include <fsu/include/file_system.hpp>

#include "file_system_private.hpp"

using namespace htps;

namespace fsu
{

FileSystem::FileSystem() : m_p{make_pimplp<FileSystemPrivate>()}
{}

FileSystem::~FileSystem() = default;

uptr<InFile> FileSystem::openFile(str const& fileName, OperationRead_t)
{
    return openFileForRead(fileName);
}

uptr<OutFile> FileSystem::openFile(str const& fileName, OperationWrite_t)
{
    return openFileForWriting(fileName);
}

uptr<InFile> FileSystem::openFileForRead(str const& fileName)
{
    return htps::muptr<InFile>(m_p->m_file_factory.inFile(fileName));
}

uptr<OutFile> FileSystem::openFileForWriting(str const&)
{
    return htps::uptr<OutFile>{};
}

FileSystem createNullFileSystem()
{
    return {};
}

}  // namespace fsu
