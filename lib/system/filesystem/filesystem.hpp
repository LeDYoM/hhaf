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
        FileSystem(core::SystemProvider &system_provider);
        ~FileSystem() override;

        RawMemory loadBinaryFile(const str& fileName);

    private:
        class FileSystemPrivate;
        uptr<FileSystemPrivate> priv_;
    };
}

#endif
