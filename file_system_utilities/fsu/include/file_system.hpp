FSU_PRAGMA_ONCE
#ifndef FSU_FILE_SYSTEM_INCLUDE_HPP
#define FSU_FILE_SYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/unique_ptr.hpp>

namespace fsu
{
class InFile;
class OutFile;

struct OperationRead {};
struct OperationWrite {};

class FileSystem
{
public:
    htps::uptr<InFile> openFile(htps::str const& fileName, OperationRead);
    htps::uptr<OutFile> openFile(htps::str const& fileName, OperationWrite);

    htps::uptr<InFile> openFileForRead(htps::str const& fileName);
    htps::uptr<OutFile> openFileForWriting(htps::str const& fileName);
};
}  // namespace fsu

#endif
