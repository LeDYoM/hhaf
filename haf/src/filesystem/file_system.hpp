HTPS_PRAGMA_ONCE
#ifndef HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP
#define HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP

#include <haf/include/core/types.hpp>

#include <haf/include/filesystem/path.hpp>
#include <haf/include/filesystem/ifile_serializer.hpp>
#include <haf/include/filesystem/ibinary_file_reader.hpp>
#include "system/system_base.hpp"
#include "haf_private.hpp"

namespace haf::sys
{
class HAF_PRIVATE FileSystem final : public SystemBase,
                                     public IFileSerializer,
                                     public fs::IBinaryFileReader
{
public:
    using SystemBase::SystemBase;
    bool fileExists(const Path& path);

    bool processResult(IFileSerializer::Result const result,
                       htps::str const& pre_message,
                       Path const& file,
                       bool const assert_on_error) override;

    core::RawMemory loadBinaryFile(Path const& file_name) override;
    htps::str loadTextFile(const Path& file_name) override;

    bool saveTextFile(const Path& file_name, const htps::str& data) override;

    IFileSerializer::Result deserializeFromFile(
        const Path& file_name,
        data::IDeserializable& data) override;

    IFileSerializer::Result serializeToFile(
        const Path& file_name,
        const data::ISerializable& data) override;
};
}  // namespace haf::sys

#endif
