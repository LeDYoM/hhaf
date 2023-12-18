#include <fsu/include/directory.hpp>

using namespace htps;

namespace fsu
{
struct Directory::DirectoryPrivate
{

};

Directory::Directory() : m_p{make_pimplp<DirectoryPrivate>()}
{}

Directory::~Directory() = default;

Directory::Directory(Directory&& other) = default;

Directory& Directory::operator=(Directory&&) = default;

uptr<InFile> Directory::openFile(str const& fileName, OperationRead_t)
{
    return openFileForRead(fileName);
}

uptr<OutFile> Directory::openFile(str const& fileName, OperationWrite_t)
{
    return openFileForWriting(fileName);
}

uptr<InFile> Directory::openFileForRead(str const& fileName)
{
    auto&& file_driver{m_p->m_file_factory.inFile(fileName)};
    return file_driver != nullptr ? htps::muptr<InFile>(htps::move(file_driver))
                                  : nullptr;
}

uptr<OutFile> Directory::openFileForWriting(str const&)
{
    return htps::uptr<OutFile>{};
}

}  // namespace fsu
