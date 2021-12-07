#ifndef HAF_SYSTEM_FILESYSTEM_PRIVATE_FUNCS_INCLUDE_HPP
#define HAF_SYSTEM_FILESYSTEM_PRIVATE_FUNCS_INCLUDE_HPP

#include <htypes/include/types.hpp>

#include <haf/include/filesystem/path.hpp>
#include "haf_private.hpp"
#include <fstream>

namespace haf::sys::detail
{
template <typename InnerType>
htps::uptr<InnerType[]> readBuffer(htps::uptr<InnerType[]> buffer,
                             const Path& file_name,
                             const htps::size_type file_size)
{
    // Alias for the char type we are going to use to read the file
    using char_type = typename std::ifstream::char_type;

    // Check that the passed InnerType has the same size
    static_assert(sizeof(InnerType) == sizeof(char_type));

    {
        // Open the file to read in binary mode
        std::ifstream input_file_stream{file_name.c_str(), std::ios::binary};
        // Get a pointer to the buffer but transforming the type to
        // the one we are going to read
        auto* buffer_char{reinterpret_cast<char_type*>(buffer.get())};

        // Read the buffer.
        input_file_stream.read(buffer_char, file_size);
    }

    return buffer;
}

bool fileExists(Path const& path);
htps::size_type fileSize(Path const& path);
}  // namespace haf::sys::detail

#endif
