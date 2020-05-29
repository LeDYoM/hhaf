#pragma once

#ifndef HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP
#define HAF_FILESYSTEM_FILE_SERIALIZER_VIEW_DATA_WRAPPER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/serializer.hpp>
#include <haf/filesystem/include/path.hpp>
#include <haf/system/include/idatawrapper.hpp>

namespace haf::sys
{
/**
 * @brief Component to provider access to file serialization operations.
 */
class FileSerializer : public sys::IDataWrapper
{
public:
    mtps::str loadTextFile(const Path &file_name);
    bool saveFile(const Path &file_name, const mtps::str&data);

    template <typename T>
    bool deserializeFromFile(const Path &file_name, T &data)
    {
        const mtps::str text_data{loadTextFile(file_name)};
        if (!text_data.empty())
        {
            return mtps::Serializer<T>::deserialize(text_data, data);
        }
        return false;
    }

    template <typename T>
    bool serializeToFile(const Path &file_name, const T &data)
    {
        return saveFile(file_name, mtps::Serializer<T>::serialize(data));
    }
};

} // namespace haf::scene

#endif
