#include "in_file_private.hpp"
#include <string>

using namespace htps;

namespace fsu
{
InFile::InFilePrivate::InFilePrivate(htps::uptr<IInFile> file_driver) :
    m_file_driver{htps::move(file_driver)}
{}

str InFile::InFilePrivate::readLine()
{
    str temp;
    m_file_driver->readLine(temp);
    return temp;
}

bool InFile::InFilePrivate::readLine(str& line)
{
    return m_file_driver->readLine(line);
}

InFile::InFilePrivate::operator bool() const noexcept
{
    return m_file_driver->isOk();
}

}  // namespace fsu
