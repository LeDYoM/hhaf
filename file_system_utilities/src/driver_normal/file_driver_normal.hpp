FSU_PRAGMA_ONCE
#ifndef FSU_FILE_DRIVER_NORMAL_INCLUDE_HPP
#define FSU_FILE_DRIVER_NORMAL_INCLUDE_HPP

#include <fsu/include/ifile_driver.hpp>

namespace fsu
{
class FileDriverNormal : public IFileDriver
{
public:
    htps::uptr<IInFile> openForRead(htps::str const& fileName) override;
};
}  // namespace fsu

#endif
