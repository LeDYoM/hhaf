export module haf:file_system:ibinary_file_reader;

HTPS_PRAGMA_ONCE
#ifndef HAF_FILESYSTEM_IBINARY_FILE_READER_INCLUDE_HPP
#define HAF_FILESYSTEM_IBINARY_FILE_READER_INCLUDE_HPP

#include <haf/include/filesystem/path.hpp>

import htypes;

namespace haf::fs
{
class IBinaryFileReader
{
protected:
    virtual ~IBinaryFileReader() = default;

public:
    virtual htps::RawMemory loadBinaryFile(sys::Path const& file_name) = 0;
};

}  // namespace haf::fs

#endif
