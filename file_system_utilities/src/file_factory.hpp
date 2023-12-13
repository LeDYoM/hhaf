FSU_PRAGMA_ONCE
#ifndef FSU_FILE_FACTORY_INCLUDE_HPP
#define FSU_FILE_FACTORY_INCLUDE_HPP

#include <fsu/include/file_system.hpp>
#include <htypes/include/unique_ptr.hpp>
#include <htypes/include/p_impl_pointer.hpp>
#include <htypes/include/str.hpp>
#include "iin_file.hpp"

namespace fsu
{
class FileFactory
{
public:
    FileFactory();
    ~FileFactory();

    htps::uptr<IInFile> inFile(htps::str const& file_name);
private:
    struct FileFactoryPrivate;
    htps::PImplPointer<FileFactoryPrivate> m_p;
};

}  // namespace fsu

#endif
