#include "in_file_normal.hpp"
#include <string>

using namespace htps;

namespace fsu
{
InFileNormal::InFileNormal(std::ifstream file) : m_file{htps::move(file)}
{}

str InFileNormal::readLine()
{
    if (m_file)
    {
        std::string temp;
        std::getline(m_file, temp);
        return str{temp.c_str()};
    }
    return {};
}

bool InFileNormal::readLine(str& line)
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

bool InFileNormal::isOk() const
{
    return static_cast<bool>(m_file);
}

}  // namespace fsu