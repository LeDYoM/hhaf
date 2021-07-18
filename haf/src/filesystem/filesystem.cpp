#include "filesystem.hpp"

#include <hlog/include/hlog.hpp>

#include <filesystem>
#include <string>
#include <fstream>

using namespace htps;

namespace haf::sys
{
namespace
{
template <typename InnerType>
uptr<InnerType[]> readBuffer(uptr<InnerType[]> buffer,
                             const Path& file_name,
                             const size_type file_size)
{
    // Alias for the char type we are going to use to read the file
    using char_type = typename std::ifstream::char_type;

    // Check that the passed InnerType has the same size
    static_assert(sizeof(InnerType) == sizeof(char_type));

    {
        // Open the file to read in binary mode
        std::ifstream ifs(file_name.c_str(), std::ios::binary);
        // Get a pointer to the buffer but transforming the type to
        // the one we are going to read
        char_type* buffer_char = reinterpret_cast<char_type*>(buffer.get());

        // Read the buffer.
        ifs.read(buffer_char, file_size);
        ifs.close();
    }

    return buffer;
}
}  // namespace

RawMemory FileSystem::loadBinaryFile(const Path& file_name)
{
    if (fileExists(file_name))
    {
        // Note function returns size_max. size_type is maximum 4GB for a file.
        size_type file_size = static_cast<size_type>(
            std::filesystem::file_size(file_name.c_str()));

        uptr<std::byte[]> buf{muptr<std::byte[]>(file_size)};
        buf = readBuffer(std::move(buf), file_name, file_size);
        return RawMemory{std::move(buf), file_size};
    }
    return RawMemory{};
}

bool FileSystem::fileExists(const Path& path)
{
    return std::filesystem::exists(std::filesystem::path(path.c_str()));
}

str FileSystem::loadTextFile(const Path& file_name)
{
    if (fileExists(file_name))
    {
        // Note: function returns size_max. size_type is maximum 4GB for a file.
        size_type file_size = static_cast<size_type>(
            std::filesystem::file_size(file_name.c_str()));

        uptr<str::value_type[]> buf{muptr<str::value_type[]>(file_size + 1U)};
        buf = readBuffer(std::move(buf), file_name, file_size);

        buf[file_size] = static_cast<str::value_type>(0);
        return str(buf.get());
    }
    return str{};
}

bool FileSystem::saveFile(const Path& file_name, const str& data)
{
    // Open a file
    std::ofstream file(file_name.c_str());
    // Everything is correct by default
    bool correct{true};

    // If file open successfully
    if (file)
    {
        // Read the data
        file << data.c_str();
        // Correct is the status of the file object after reading it
        correct = file.good();
        file.close();
    }

    if (!file || !correct)
    {
        DisplayLog::error("Cannot write text file ", file_name);
    }

    return (file && correct);
}

}  // namespace haf::sys
