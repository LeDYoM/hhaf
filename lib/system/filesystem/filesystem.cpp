#include "filesystem.hpp"

#include <logger/include/log.hpp>

#include <filesystem>
#include <string>
#include <fstream>

namespace lib::core
{
    class FileSystem::FileSystemPrivate
    {
    public:
    };

	FileSystem::FileSystem(core::SystemProvider &system_provider)
        : HostedAppService{ system_provider },
        priv_ { muptr<FileSystemPrivate>() } {}

	FileSystem::~FileSystem() = default;

	RawMemory FileSystem::loadBinaryFile(const str & fileName)
	{
		
		//Note function returns size_max. size_type is maximum 4GB for a file.
		size_type fileSize = static_cast<size_type>(std::filesystem::file_size(fileName.c_str()));

		uptr<std::byte[]> buf{ muptr<std::byte[]>(fileSize) };
		std::basic_ifstream<std::byte> ifs(fileName.c_str(), std::ios::binary);
		ifs.read(buf.get(), fileSize);
		return RawMemory{ std::move(buf), fileSize };
		
	}
}
