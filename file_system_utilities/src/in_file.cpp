#include <fsu/include/in_file.hpp>
#include <fsu/include/file_system.hpp>
#include "in_file_private.hpp"

#include <fstream>

using namespace htps;

namespace fsu
{
InFile::InFile(FileSystem& file_system_parent, str const& file_name) :
    m_p{make_pimplp<InFilePrivate>(file_system_parent,
        std::fstream{file_name.c_str(), std::ios::in})}
{}

InFile::~InFile() = default;

string_vector InFile::readTextFile()
{
    string_vector result;
    bool is_read{readTextFile(result)};
    (void)(is_read);
    return result;
}

bool InFile::readTextFile(string_vector& str_data)
{
    bool continue_reading{static_cast<bool>(*m_p)};
    str_data.clear();

    if (continue_reading)
    {
        while(continue_reading)
        {
            str temp;
            continue_reading = m_p->readLine(temp);
            str_data.push_back(htps::move(temp));
        }
        return true;
    }
    return false;
}

}  // namespace fsu
