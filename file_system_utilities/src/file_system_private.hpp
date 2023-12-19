FSU_PRAGMA_ONCE
#ifndef FSU_FILE_SYSTEM_PRIVATE_INCLUDE_HPP
#define FSU_FILE_SYSTEM_PRIVATE_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <fsu/include/file_system.hpp>
#include "file_factory.hpp"

namespace fsu
{
struct FileSystem::FileSystemPrivate
{
    FileFactory m_file_factory;
};

}  // namespace fsu

#endif
