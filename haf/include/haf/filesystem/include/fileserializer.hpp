#pragma once

#ifndef HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/object_utils.hpp>
#include <mtypes/include/serializer.hpp>
#include <haf/filesystem/include/path.hpp>
#include <haf/system/include/idatawrapper.hpp>
#include <haf/shareddata/include/ishareable.hpp>

namespace haf::sys
{
/**
 * @brief Component to provider access to file serialization operations.
 */
class FileSerializer : public sys::IDataWrapper
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
    Result deserializeFromFile(const Path& file_name, T& data)
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

    Result deserializeFromFile2(const Path& file_name, shdata::IShareable& data)
    {
        const mtps::str text_data{loadTextFile(file_name)};
        if (!text_data.empty())
        {
            mtps::ObjectCompiler obj_compiler(text_data);
            if (obj_compiler.compile())
            {
                // The compilation was correct so, at least we
                // have a valid Object.
                return ((data.deserialize(obj_compiler.result()))
                            ? Result::Success
                            : Result::ParsingError);
            }
            else
            {
                return Result::ParsingError;
            }
        }
        else
        {
            return Result::FileIOError;
        }        
    }

    template <typename T>
    Result serializeToFile(const Path& file_name, const T& data)
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

    Result serializeToFile2(const Path& file_name,
                            const shdata::IShareable& data)
    {
        //        auto temp{mtps::Serializer<T>::serialize(data)};
        mtps::Object obj;
        auto temp(data.serialize(obj));

        if (temp)
        {
            mtps::str data_str;
            data_str << obj;

            return ((saveFile(file_name, std::move(data_str)))
                        ? Result::Success
                        : Result::FileIOError);
        }
        return Result::ParsingError;
    }
};

}  // namespace haf::sys

#endif
