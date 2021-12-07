#ifndef HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP
#define HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/rawmemory.hpp>

#include <haf/include/filesystem/path.hpp>
#include <haf/include/filesystem/ifile_serializer.hpp>
#include "system/systembase.hpp"
#include "haf_private.hpp"

namespace haf::sys
{
class HAF_PRIVATE FileSystem final : public SystemBase, public IFileSerializer
{
public:
    using SystemBase::SystemBase;
    bool fileExists(const Path& path);

    bool processResult(IFileSerializer::Result const result,
                       htps::str const& pre_message,
                       Path const& file,
                       bool const assert_on_error) override;

    htps::RawMemory loadBinaryFile(const htps::str& file_name);
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
