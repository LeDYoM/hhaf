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

    htps::str loadTextFile(const Path& file_name);

    bool saveFile(const Path& file_name, const htps::str& data);

    template <typename T>
    Result deserializeFromFileTemplate(const Path& file_name, T& data)
    {
        const htps::str text_data{loadTextFile(file_name)};
        if (!text_data.empty())
        {
            return ((htps::Serializer<T>::deserialize(text_data, data))
                        ? Result::Success
                        : Result::ParsingError);
        }
        return Result::FileIOError;
    }

    Result deserializeFromFile(const Path& file_name,
                               data::IDeserializable& data);

    template <typename T>
    Result serializeToFileTemplate(const Path& file_name, const T& data)
    {
        auto temp{htps::Serializer<T>::serialize(data)};
        if (!temp.empty())
        {
            return ((saveFile(file_name, std::move(temp)))
                        ? Result::Success
                        : Result::FileIOError);
        }
        return Result::ParsingError;
    }

    Result serializeToFile(const Path& file_name,
                           const data::ISerializable& data);
};

}  // namespace haf::sys

#endif
