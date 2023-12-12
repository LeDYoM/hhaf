FSU_PRAGMA_ONCE
#ifndef FSU_FILE_FACTORY_INCLUDE_HPP
#define FSU_FILE_FACTORY_INCLUDE_HPP

#include <fsu/include/file_system.hpp>
#include <htypes/include/unique_ptr.hpp>
#include <htypes/include/str.hpp>
#include "iin_file.hpp"

namespace fsu
{
class FileSystemFileFactory
{
public:
    htps::uptr<IInFile> inFile(htps::str const& file_name);
};

}  // namespace fsu

#endif
