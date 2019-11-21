#pragma once

#ifndef LIB_SYSTEM_FILESYSTEM_INCLUDE_HPP
#define LIB_SYSTEM_FILESYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/serializer.hpp>

#include <lib/system/appservice.hpp>

#include "file.hpp"

namespace lib::core
{
    class FileSystem final : public HostedAppService
    {
    public:
        using Path = str;

        FileSystem(core::SystemProvider &system_provider);
        ~FileSystem() override;

        bool fileExists(const Path& path);

        RawMemory loadBinaryFile(const str& file_name);
        str loadTextFile(const Path& file_name);

        bool saveFile(const Path& file_name, const str& data);

        template <typename T>
        bool deserializeFromFile(const Path& file_name, T& data)
        {
            const str text_data{loadTextFile(file_name)};
            if (!text_data.empty())
            {
                return Serializer<T>::deserialize(text_data, data);
            }
            return false;
        }

        template <typename T>
        bool serializeToFile(const Path& file_name, const T& data)
        {
            return saveFile(file_name, Serializer<T>::serialize(data));
        }

    private:
        class FileSystemPrivate;
        uptr<FileSystemPrivate> priv_;
    };
}

#endif
