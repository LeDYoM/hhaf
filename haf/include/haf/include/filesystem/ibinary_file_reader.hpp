HAF_PRAGMA_ONCE
#ifndef HAF_FILESYSTEM_IBINARY_FILE_READER_INCLUDE_HPP
#define HAF_FILESYSTEM_IBINARY_FILE_READER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/filesystem/path.hpp>

namespace haf::fs
{
class IBinaryFileReader
{
protected:
    virtual ~IBinaryFileReader() = default;

public:
    virtual core::RawMemory loadBinaryFile(sys::Path const& file_name) = 0;
};

}  // namespace haf::fs

#endif
