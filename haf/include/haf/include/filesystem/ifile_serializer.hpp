#ifndef HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
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
    enum class Result : htps::u8
    {
        Success      = 0U,
        FileIOError  = 1U,
        ParsingError = 2U
    };

    virtual bool processResult(Result const result,
                       htps::str const& pre_message,
                       Path const& file,
                       bool const assert_on_error) = 0;

    virtual htps::str loadTextFile(const Path& file_name) = 0;

    virtual bool saveTextFile(const Path& file_name, const htps::str& data) = 0;

    virtual Result deserializeFromFile(const Path& file_name,
                               data::IDeserializable& data);

    virtual Result serializeToFile(const Path& file_name,
                           const data::ISerializable& data);
};

}  // namespace haf::sys

#endif
