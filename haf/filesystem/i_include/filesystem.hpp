#pragma once

#ifndef HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP
#define HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/serializer.hpp>
#include <mtypes/include/rawmemory.hpp>

#include <haf/system/include/appservice.hpp>

namespace haf::sys
{
class FileSystem final : public AppService
{
public:
    using Path = mtps::str;

    FileSystem(sys::SystemProvider &system_provider);
    ~FileSystem() override;

    bool fileExists(const Path &path);

    mtps::RawMemory loadBinaryFile(const mtps::str&file_name);
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

private:
    class FileSystemPrivate;
    mtps::uptr<FileSystemPrivate> priv_;
};
} // namespace haf::sys

#endif
