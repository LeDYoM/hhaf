HAF_PRAGMA_ONCE
#ifndef HAF_SYSTEM_FILESYSTEM_PRIVATE_FUNCS_INCLUDE_HPP
#define HAF_SYSTEM_FILESYSTEM_PRIVATE_FUNCS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/filesystem/path.hpp>
#include "haf_private.hpp"
#include <fstream>

namespace haf::sys::detail
{
template <typename InnerType>
core::vector<InnerType> readBuffer(core::vector<InnerType>&& buffer,
                                   const Path& file_name,
                                   const htps::size_type file_size)
{
    // Alias for the char type we are going to use to read the file
    using char_type = typename std::ifstream::char_type;

    // Check that the passed InnerType has the same size
    static_assert(sizeof(InnerType) == sizeof(char_type));

    {
        // Open the file to read in binary mode
        if (std::ifstream input_file_stream{file_name.c_str(),
                                            std::ios::binary};
            input_file_stream)
        {
            buffer.resize(file_size);

            // Read the buffer.
            input_file_stream.read(buffer.begin(), file_size);
        }
    }

    return buffer;
}

bool fileExists(Path const& path);
htps::size_type fileSize(Path const& path);
}  // namespace haf::sys::detail

#endif
