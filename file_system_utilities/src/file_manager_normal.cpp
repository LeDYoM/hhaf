#include "file_manager_normal.hpp"
#include "in_file_normal.hpp"
#include <fstream>

using namespace htps;

namespace fsu
{
bool FileManagerNormal::exists(htps::str const& /*fileName*/)
{
    return true;
}

htps::uptr<IInFile> FileManagerNormal::openForRead(htps::str const& fileName)
{
    return htps::muptr<InFileNormal>(
        std::ifstream{fileName.c_str(), std::ios::in});
}

}  // namespace fsu
