#ifndef HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/object_utils.hpp>
#include <htypes/include/serializer.hpp>
#include <haf/include/filesystem/path.hpp>
#include <haf/include/system/idatawrapper.hpp>
#include <haf/include/shareddata/ishareable.hpp>
#include <haf/include/haf_export.hpp>

namespace haf::sys
{
/**
 * @brief Component to provider access to file serialization operations.
 */
class HAF_API FileSerializer : public sys::IDataWrapper
{
public:
    enum class Result : htps::u8
    {
        Success      = 0U,
        FileIOError  = 1U,
        ParsingError = 2U
    };

    bool processResult(Result const result,
                       htps::str const& pre_message,
                       Path const& file,
                       bool const assert_on_error);

    htps::str loadTextFile(const Path& file_name);

    bool saveFile(const Path& file_name, const htps::str& data);

    Result deserializeFromFile(const Path& file_name,
                               data::IDeserializable& data);

    Result serializeToFile(const Path& file_name,
                           const data::ISerializable& data);
};

}  // namespace haf::sys

#endif
