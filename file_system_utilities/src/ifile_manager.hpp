FSU_PRAGMA_ONCE
#ifndef FSU_I_FILE_MANAGER_INCLUDE_HPP
#define FSU_I_FILE_MANAGER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

namespace fsu
{
class IInFile;

class IFileManager
{
public:
    virtual bool exists(htps::str const& fileName) = 0;
    virtual htps::uptr<IInFile> openForRead(htps::str const& fileName) = 0;

    virtual ~IFileManager() = default;
};
}  // namespace fsu

#endif
