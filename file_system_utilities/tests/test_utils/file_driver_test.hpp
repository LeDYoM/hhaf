#ifndef FILE_DRIVER_TEST_INCLUDE_HPP
#define FILE_DRIVER_TEST_INCLUDE_HPP

#include "in_file_test.hpp"
#include <htypes/include/types.hpp>

namespace fsu_test
{
class FileDriverTest : public fsu::IFileDriver
{
public:
    htps::uptr<fsu::IInFile> openForRead(htps::str const& file_name) override
    {
        auto ifile{htps::muptr<InFileTest>(file_name)};
        return ifile;
    }
};

}  // namespace fsu

#endif
