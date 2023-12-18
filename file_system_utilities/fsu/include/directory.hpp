FSU_PRAGMA_ONCE
#ifndef FSU_DIRECTORY_INCLUDE_HPP
#define FSU_DIRECTORY_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/unique_ptr.hpp>
#include <htypes/include/p_impl_pointer.hpp>

#include <fsu/include/in_file.hpp>
#include <fsu/include/out_file.hpp>

namespace fsu
{
struct OperationRead_t {};
struct OperationWrite_t {};

constexpr OperationRead_t OperationRead{};
constexpr OperationWrite_t OperationWrite{};

class Directory
{
public:
    Directory();
    ~Directory();

    Directory(Directory const&) = delete;
    Directory(Directory&&);

    Directory& operator=(Directory const&) = delete;
    Directory& operator=(Directory&&);

    htps::uptr<InFile> openFile(htps::str const& fileName, OperationRead_t);
    htps::uptr<OutFile> openFile(htps::str const& fileName, OperationWrite_t);

    htps::uptr<InFile> openFileForRead(htps::str const& fileName);
    htps::uptr<OutFile> openFileForWriting(htps::str const& fileName);
private:
    struct DirectoryPrivate;
    htps::PImplPointer<DirectoryPrivate> m_p;
};

 }  // namespace fsu

#endif
