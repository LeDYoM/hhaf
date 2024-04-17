#include <fsu/include/file_system.hpp>

#include "file_system_private.hpp"

using namespace htps;

namespace fsu
{

FileSystem::FileSystem() : m_p{make_pimplp<FileSystemPrivate>()}
{}

FileSystem::~FileSystem() = default;

FileSystem::FileSystem(FileSystem&& other) = default;

FileSystem& FileSystem::operator=(FileSystem&&) = default;

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
    auto&& file_driver{m_p->m_file_factory.inFile(fileName)};
    return file_driver != nullptr ? htps::muptr<InFile>(htps::move(file_driver))
                                  : nullptr;
}

uptr<OutFile> FileSystem::openFileForWriting(str const&)
{
    return htps::uptr<OutFile>{};
}

bool FileSystem::addFileDriver(htps::uptr<IFileDriver> ifile_driver)
{
    return m_p->m_file_factory.addDriver(htps::move(ifile_driver));
}

}  // namespace fsu
