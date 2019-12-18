#include "filesystem.hpp"

#include <lib/include/liblog.hpp>

#include <filesystem>
#include <string>
#include <fstream>

namespace lib::core
{
    class FileSystem::FileSystemPrivate
    {
    public:
        template<typename InnerType>
        uptr<InnerType[]> readBuffer(uptr<InnerType[]> buffer, const Path& file_name, const size_type file_size)
        {
            std::basic_ifstream<InnerType> ifs(file_name.c_str(), std::ios::binary);
            ifs.read(buffer.get(), file_size);
            return buffer;
        }
    };

    FileSystem::FileSystem(core::SystemProvider &system_provider)
        : HostedAppService{ system_provider },
        priv_ { muptr<FileSystemPrivate>() } {}

    FileSystem::~FileSystem() = default;

    RawMemory FileSystem::loadBinaryFile(const Path & file_name)
    {
        if (fileExists(file_name))
        {
            //Note function returns size_max. size_type is maximum 4GB for a file.
            size_type file_size = static_cast<size_type>(std::filesystem::file_size(file_name.c_str()));

            uptr<std::byte[]> buf{ muptr<std::byte[]>(file_size) };
            buf = priv_->readBuffer(std::move(buf), file_name, file_size);
            return RawMemory{ std::move(buf), file_size };
        }
        return RawMemory{};
    }

    bool FileSystem::fileExists(const Path& path)
    {
        return std::filesystem::exists(std::filesystem::path(path.c_str()));
    }

    str FileSystem::loadTextFile(const Path& file_name)
    {
        if (fileExists(file_name))
        {
            //Note function returns size_max. size_type is maximum 4GB for a file.
            size_type file_size = static_cast<size_type>(std::filesystem::file_size(file_name.c_str()));

            uptr<str::char_type[]> buf{ muptr<str::char_type[]>(file_size + 1U) };
            buf = priv_->readBuffer(std::move(buf), file_name, file_size);
            
            buf[file_size] = static_cast<str::char_type>(0);
            return str(buf.get());
        }
        return str{};
    }

    bool FileSystem::saveFile(const Path& file_name, const str& data)
    {
        std::ofstream file(file_name.c_str());
        bool correct{true};

        if (file)
        {
            file << data.c_str();
            correct = file.good();
        }

        if (!file || !correct)
        {
            log_error("Cannot write text file", file_name);
        }

        return (file && correct);
    }

}
