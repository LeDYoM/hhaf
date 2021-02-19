#ifndef HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP
#define HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rawmemory.hpp>

#include <haf/filesystem/include/path.hpp>
#include <system/i_include/systembase.hpp>

namespace haf::sys
{
class FileSystem final : public SystemBase
{
public:
    using SystemBase::SystemBase;
    bool fileExists(const Path& path);

    htps::RawMemory loadBinaryFile(const htps::str& file_name);
    htps::str loadTextFile(const Path& file_name);

    bool saveFile(const Path& file_name, const htps::str& data);
};
}  // namespace haf::sys

#endif
