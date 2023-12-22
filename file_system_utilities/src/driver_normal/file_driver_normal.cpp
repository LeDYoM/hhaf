#include "file_driver_normal.hpp"
#include "in_file_normal.hpp"
#include <fstream>

using namespace htps;

namespace fsu
{
htps::uptr<IInFile> FileDriverNormal::openForRead(htps::str const& fileName)
{
    std::ifstream file_stream{fileName.c_str(), std::ios::in};

    return file_stream.good()
        ? htps::muptr<InFileNormal>(htps::move(file_stream))
        : nullptr;
}

}  // namespace fsu
