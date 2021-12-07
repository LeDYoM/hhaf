#include "file_system_private_funcs.hpp"
#include <filesystem>

using namespace htps;

namespace haf::sys::detail
{
bool fileExists(Path const& path)
{
    return std::filesystem::exists(std::filesystem::path(path.c_str()));
}

size_type fileSize(Path const& file_name)
{
    return static_cast<size_type>(
            std::filesystem::file_size(file_name.c_str()));
}

}  // namespace haf::sys::detail
