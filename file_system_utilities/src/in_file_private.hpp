FSU_PRAGMA_ONCE
#ifndef FSU_FILE_SYSTEM_IN_FILE_PRIVATE_INCLUDE_HPP
#define FSU_FILE_SYSTEM_IN_FILE_PRIVATE_INCLUDE_HPP

#include <fsu/include/file_system.hpp>
#include <fsu/include/in_file.hpp>
#include <fsu/include/iin_file.hpp>

namespace fsu
{
class IInFile;

class InFile::InFilePrivate
{
public:
    InFilePrivate(htps::uptr<IInFile> file_driver);

    htps::str readLine();
    bool readLine(htps::str& line);

    explicit operator bool() const noexcept;
private:
    htps::uptr<IInFile> m_file_driver;
};
}  // namespace fsu

#endif
