#include "file_factory.hpp"
#include "ifile_manager.hpp"

#include <htypes/include/vector.hpp>

#include "driver_normal/in_file_normal.hpp"

using namespace htps;

namespace fsu
{
struct FileFactory::FileFactoryPrivate
{
    vector<uptr<IFileManager>> m_file_managers;
};

FileFactory::FileFactory() : m_p{htps::make_pimplp<FileFactoryPrivate>()}
{}

FileFactory::~FileFactory() = default;

uptr<IInFile> FileFactory::inFile(str const& file_name)
{
    for (auto&& file_manager : m_p->m_file_managers)
    {
        if (file_manager->exists(file_name))
        {
            return file_manager->openForRead(file_name);
        }
    }
    return nullptr;
}

}  // namespace fsu
