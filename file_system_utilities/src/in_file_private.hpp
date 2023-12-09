#include <fsu/include/file_system.hpp>
#include <fsu/include/in_file.hpp>
#include <fstream>

namespace fsu
{
class InFile::InFilePrivate
{
public:
    InFilePrivate(FileSystem& file_system, std::fstream file) :
        m_file_system{file_system}, m_file{htps::move(file)}
    {}

    htps::str readLine();
    bool readLine(htps::str& line);

    explicit operator bool() const noexcept;
private:
    FileSystem& m_file_system;
    std::fstream m_file;
};
}  // namespace fsu
