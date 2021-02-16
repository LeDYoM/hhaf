#ifndef HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/object_utils.hpp>
#include <htypes/include/serializer.hpp>
#include <haf/filesystem/include/path.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/shareddata/include/ishareable.hpp>
#include <haf/haf_export.hpp>

namespace haf::sys
{
/**
 * @brief Component to provider access to file serialization operations.
 */
class HAF_API FileSerializer : public sys::IDataWrapper
{
public:
    enum class Result : mtps::u8
    {
        Success      = 0U,
        FileIOError  = 1U,
        ParsingError = 2U
    };

    mtps::str loadTextFile(const Path& file_name);

    bool saveFile(const Path& file_name, const mtps::str& data);

    template <typename T>
    Result deserializeFromFileTemplate(const Path& file_name, T& data)
    {
        const mtps::str text_data{loadTextFile(file_name)};
        if (!text_data.empty())
        {
            return ((mtps::Serializer<T>::deserialize(text_data, data))
                        ? Result::Success
                        : Result::ParsingError);
        }
        return Result::FileIOError;
    }

    Result deserializeFromFile(const Path& file_name, shdata::IShareable& data);

    template <typename T>
    Result serializeToFileTemplate(const Path& file_name, const T& data)
    {
        auto temp{mtps::Serializer<T>::serialize(data)};
        if (!temp.empty())
        {
            return ((saveFile(file_name, std::move(temp)))
                        ? Result::Success
                        : Result::FileIOError);
        }
        return Result::ParsingError;
    }

    Result serializeToFile(const Path& file_name,
                            const shdata::IShareable& data);
};

}  // namespace haf::sys

#endif
