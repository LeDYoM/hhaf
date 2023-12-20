#include "file_driver_normal.hpp"
#include "in_file_normal.hpp"
#include <fstream>

using namespace htps;

namespace fsu
{
htps::uptr<IInFile> FileDriverNormal::openForRead(htps::str const& fileName)
{
    return htps::muptr<InFileNormal>(
        std::ifstream{fileName.c_str(), std::ios::in});
}

}  // namespace fsu
