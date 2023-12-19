FSU_PRAGMA_ONCE
#ifndef FSU_FILE_MANAGER_NORMAL_INCLUDE_HPP
#define FSU_FILE_MANAGER_NORMAL_INCLUDE_HPP

#include <fsu/include/ifile_driver.hpp>

namespace fsu
{
class FileManagerNormal : public IFileDriver
{
public:
    bool exists(htps::str const& fileName) override;
    htps::uptr<IInFile> openForRead(htps::str const& fileName) override;
};
}  // namespace fsu

#endif
