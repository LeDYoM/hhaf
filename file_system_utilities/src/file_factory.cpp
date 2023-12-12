#include "file_factory.hpp"
#include "in_file_normal.hpp"
#include <fstream>

using namespace htps;

namespace fsu
{
uptr<IInFile> FileSystemFileFactory::inFile(str const& file_name)
{
    return htps::muptr<InFileNormal>(
        std::ifstream{file_name.c_str(), std::ios::in});
}

}  // namespace fsu
