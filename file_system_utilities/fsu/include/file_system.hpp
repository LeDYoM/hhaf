FSU_PRAGMA_ONCE
#ifndef FSU_FILE_SYSTEM_INCLUDE_HPP
#define FSU_FILE_SYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/unique_ptr.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <fsu/include/in_file.hpp>
#include <fsu/include/out_file.hpp>
#include <fsu/include/ifile_driver.hpp>

namespace fsu
{
struct OperationRead_t {};
struct OperationWrite_t {};

constexpr OperationRead_t OperationRead{};
constexpr OperationWrite_t OperationWrite{};

class IFileDriver;

class FileSystem
{
public:
    FileSystem();
    ~FileSystem();

    FileSystem(FileSystem const&) = delete;
    FileSystem(FileSystem&&);

    FileSystem& operator=(FileSystem const&) = delete;
    FileSystem& operator=(FileSystem&&);

    htps::uptr<InFile> openFile(htps::str const& fileName, OperationRead_t);
    htps::uptr<OutFile> openFile(htps::str const& fileName, OperationWrite_t);

    htps::uptr<InFile> openFileForRead(htps::str const& fileName);
    htps::uptr<OutFile> openFileForWriting(htps::str const& fileName);

    bool addFileDriver(htps::uptr<IFileDriver> ifile_driver);

private:
    struct FileSystemPrivate;
    htps::PImplPointer<FileSystemPrivate> m_p;
};

 }  // namespace fsu

#endif
