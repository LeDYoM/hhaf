#include "in_file_private.hpp"
#include <string>

using namespace htps;

namespace fsu
{
str InFile::InFilePrivate::readLine()
{
    if (m_file)
    {
        std::string temp;
        std::getline(m_file, temp);
        return str{temp.c_str()};
    }
    return {};
}

bool InFile::InFilePrivate::readLine(str& line)
{
    if (m_file)
    {
        std::string temp;
        std::getline(m_file, temp);
        line = temp.c_str();
        return true;
    }
    return false;
}

InFile::InFilePrivate::operator bool() const noexcept
{
    return static_cast<bool>(m_file);
}

}  // namespace fsu
