#include "filesystem.hpp"

#include <lib/include/core/log.hpp>

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

	FileInputBinary FileSystem::loadBinaryFile(const str & fileName)
	{
		//Note function returns size_max. size_type is maximum 4GB for a file.
		size_type fileSize = static_cast<size_type>(std::filesystem::file_size(fileName.c_str()));

		uptr<char[]> buf{ muptr<char[]>(fileSize) };
		std::basic_ifstream<char> ifs(fileName.c_str(), std::ios::binary);
		ifs.read(buf.get(), fileSize);
		return FileInputBinary(std::move(buf), fileSize);
	}
}
