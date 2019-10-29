#pragma once

#ifndef LIB_SYSTEM_FILESYSTEM_INCLUDE_HPP
#define LIB_SYSTEM_FILESYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
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

    private:
        class FileSystemPrivate;
        uptr<FileSystemPrivate> priv_;
    };
}

#endif
