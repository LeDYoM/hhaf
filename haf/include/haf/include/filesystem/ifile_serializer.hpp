HAF_PRAGMA_ONCE
#ifndef HAF_FILESYSTEM_IFILE_SERIALIZER_INCLUDE_HPP
#define HAF_FILESYSTEM_IFILE_SERIALIZER_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/filesystem/path.hpp>
#include <haf/include/shareddata/ishareable.hpp>

namespace haf::sys
{
/**
 * @brief Component to provider access to file serialization operations.
 */
class IFileSerializer
{
public:
    enum class Result : core::u8
    {
        Success      = 0U,
        FileIOError  = 1U,
        ParsingError = 2U
    };

    virtual bool processResult(Result const result,
                               core::str const& pre_message,
                               Path const& file,
                               bool const assert_on_error) = 0;

    virtual core::str loadTextFile(const Path& file_name) = 0;

    virtual bool saveTextFile(const Path& file_name, const core::str& data) = 0;

    virtual Result deserializeFromFile(const Path& file_name,
                                       data::IDeserializable& data) = 0;

    virtual Result serializeToFile(const Path& file_name,
                                   const data::ISerializable& data) = 0;
};

}  // namespace haf::sys

#endif
