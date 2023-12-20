#ifndef FILE_DRIVER_TEST_INCLUDE_HPP
#define FILE_DRIVER_TEST_INCLUDE_HPP

#include <fsu/include/ifile_driver.hpp>

namespace fsu_test
{
class FileDriverTest : public fsu::IFileDriver
{
public:
    htps::uptr<fsu::IInFile> openForRead(htps::str const& fileName) override;
};

}  // namespace fsu

#endif
