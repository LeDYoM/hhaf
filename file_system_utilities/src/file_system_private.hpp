FSU_PRAGMA_ONCE
#ifndef FSU_FILE_SYSTEM_PRIVATE_INCLUDE_HPP
#define FSU_FILE_SYSTEM_PRIVATE_INCLUDE_HPP

#include <fsu/include/file_system.hpp>
#include "file_factory.hpp"

namespace fsu
{
struct FileSystem::FileSystemPrivate
{
    FileSystemFileFactory m_file_factory;
};

}  // namespace fsu

#endif
