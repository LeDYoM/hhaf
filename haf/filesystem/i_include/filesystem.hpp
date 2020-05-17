#pragma once

#ifndef HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP
#define HAF_SYSTEM_FILESYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector.hpp>
#include <mtypes/include/rawmemory.hpp>

#include <haf/filesystem/include/path.hpp>
#include <system/i_include/appservice.hpp>

namespace haf::sys
{
class FileSystem final : public AppService
{
public:

    FileSystem(sys::SystemProvider &system_provider);
    ~FileSystem() override;

    bool fileExists(const Path &path);

    mtps::RawMemory loadBinaryFile(const mtps::str&file_name);
    mtps::str loadTextFile(const Path &file_name);

    bool saveFile(const Path &file_name, const mtps::str&data);

private:
    class FileSystemPrivate;
    mtps::uptr<FileSystemPrivate> priv_;
};
} // namespace haf::sys

#endif
