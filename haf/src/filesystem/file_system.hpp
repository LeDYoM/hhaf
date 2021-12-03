#ifndef HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP
#define HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rawmemory.hpp>

#include <haf/include/filesystem/path.hpp>
#include "system/systembase.hpp"
#include "haf_private.hpp"

namespace haf::sys
{
class HAF_PRIVATE FileSystem final : public SystemBase
{
public:
    using SystemBase::SystemBase;
    bool fileExists(const Path& path);

    htps::RawMemory loadBinaryFile(const htps::str& file_name);
    htps::str loadTextFile(const Path& file_name);
    bool saveTextFile(const Path& file_name, const htps::str& data);
};
}  // namespace haf::sys

#endif
