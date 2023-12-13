FSU_PRAGMA_ONCE
#ifndef FSU_FILE_SYSTEM_INCLUDE_HPP
#define FSU_FILE_SYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/unique_ptr.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <fsu/include/in_file.hpp>
#include <fsu/include/out_file.hpp>

namespace fsu
{
struct OperationRead {};
struct OperationWrite {};

class FileSystem
{
public:
    FileSystem();
    ~FileSystem();

    htps::uptr<InFile> openFile(htps::str const& fileName, OperationRead);
    htps::uptr<OutFile> openFile(htps::str const& fileName, OperationWrite);

    htps::uptr<InFile> openFileForRead(htps::str const& fileName);
    htps::uptr<OutFile> openFileForWriting(htps::str const& fileName);
private:
    struct FileSystemPrivate;
    htps::PImplPointer<FileSystemPrivate> m_p;
};

FileSystem createNullFileSystem();

}  // namespace fsu

#endif
